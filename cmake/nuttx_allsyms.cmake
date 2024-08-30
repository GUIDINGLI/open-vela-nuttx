# ##############################################################################
# cmake/nuttx_allsyms.cmake
#
# Licensed to the Apache Software Foundation (ASF) under one or more contributor
# license agreements.  See the NOTICE file distributed with this work for
# additional information regarding copyright ownership.  The ASF licenses this
# file to you under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License.  You may obtain a copy of
# the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
# License for the specific language governing permissions and limitations under
# the License.
#
# ##############################################################################

# ~~~
# define_allsyms_link_target
#
# Description:
#   Wrapper of cmake declaration of nuttx executable
#   in order to implement ALLSYMS.
#
#   When declaring the target to be `nuttx`,
#   create an empty allsyms source file for it;
#   When the target is declared as something else,
#   the link behavior of the `nuttx` target is cloned
#   and added to actually generate the allsyms file.
#
# Parameters:
#   inter_target         : declaration of target
#   dep_target           : targets which depends on
#   allsyms_file         : generated allsyms file name
# ~~~
macro(define_allsyms_link_target inter_target dep_target allsyms_file)
  if(${inter_target} STREQUAL nuttx)
    # create an empty allsyms source file for `nuttx`
    set(ALLSYMS_SOURCE ${CMAKE_BINARY_DIR}/allsyms_empty.c)
    if(NOT EXISTS ${ALLSYMS_SOURCE})
      file(WRITE ${ALLSYMS_SOURCE} "#include <nuttx/compiler.h>\n\n")
      file(APPEND ${ALLSYMS_SOURCE} "#include <nuttx/symtab.h>\n")
      file(APPEND ${ALLSYMS_SOURCE} "extern int g_nallsyms;\n\n")
      file(APPEND ${ALLSYMS_SOURCE} "extern struct symtab_s g_allsyms[];\n\n")
      file(APPEND ${ALLSYMS_SOURCE} "int g_nallsyms = 1;\n\n")
      file(
        APPEND ${ALLSYMS_SOURCE}
        "struct symtab_s g_allsyms[1] = {{ \"Unknown\", (FAR  void *)0x00000000 }};\n\n"
      )
    endif()
    target_sources(nuttx PRIVATE ${ALLSYMS_SOURCE})
    set(ALLSYMS_INCDIR ${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/include)
    set_source_files_properties(
      ${ALLSYMS_SOURCE} PROPERTIES INCLUDE_DIRECTORIES "${ALLSYMS_INCDIR}")
  else()
    # generate `g_allsyms` file
    add_custom_command(
      OUTPUT ${allsyms_file}.c POST_BUILD
      COMMAND ${NUTTX_DIR}/tools/mkallsyms.py ${CMAKE_BINARY_DIR}/${dep_target}
              ${allsyms_file}.c
      DEPENDS ${dep_target}
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
      COMMAND_EXPAND_LISTS)

    # relink target with allsysm.c which generated by the elf of the previous
    # phase
    add_executable(
      ${inter_target} ${allsyms_file}.c
                      $<FILTER:$<TARGET_OBJECTS:nuttx>,EXCLUDE,allsyms_empty>)

    # relink target and nuttx have exactly the same configuration
    target_include_directories(
      ${inter_target} SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/include
                                    ${CMAKE_BINARY_DIR}/include)
    target_compile_definitions(
      ${inter_target} PRIVATE $<TARGET_PROPERTY:nuttx,NUTTX_KERNEL_DEFINITIONS>)
    target_compile_options(
      ${inter_target}
      PRIVATE $<TARGET_PROPERTY:nuttx,NUTTX_KERNEL_COMPILE_OPTIONS>)
    target_link_options(${inter_target} PRIVATE
                        $<TARGET_PROPERTY:nuttx,LINK_OPTIONS>)
    target_link_libraries(
      ${inter_target}
      PRIVATE $<TARGET_GENEX_EVAL:nuttx,$<TARGET_PROPERTY:nuttx,LINK_LIBRARIES>>
    )
  endif()
endmacro()

# nuttx link with allsysm
define_allsyms_link_target(nuttx NULL NULL)
# allsyms link phase 1 with generated allsyms source file
define_allsyms_link_target(allsyms_inter nuttx allsyms_first_link)
# allsyms link phase 2 since the table offset may changed
define_allsyms_link_target(allsyms_nuttx allsyms_inter allsyms_final_link)
# fixing timing dependencies
add_dependencies(nuttx_post allsyms_nuttx)
# finally use allsyms_nuttx to overwrite the already generated nuttx
add_custom_command(
  TARGET allsyms_nuttx
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different allsyms_nuttx nuttx DEPENDS
          allsyms_nuttx
  COMMENT "Overwrite nuttx with allsyms_nuttx")

# regenerate binary outputs in different formats (.bin, .hex, etc)
if(CONFIG_INTELHEX_BINARY)
  add_custom_command(
    TARGET allsyms_nuttx
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex allsyms_nuttx nuttx.hex DEPENDS nuttx-hex
    COMMENT "Regenerate nuttx.hex")

endif()
if(CONFIG_MOTOROLA_SREC)
  add_custom_command(
    TARGET allsyms_nuttx
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O srec allsyms_nuttx nuttx.srec DEPENDS nuttx-srec
    COMMENT "Regenerate nuttx.srec")
endif()
if(CONFIG_RAW_BINARY)
  add_custom_command(
    TARGET allsyms_nuttx
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary allsyms_nuttx nuttx.bin DEPENDS nuttx-bin
    COMMENT "Regenerate nuttx.bin")
endif()
