/****************************************************************************
 * libs/libc/pthread/pthread_mutexattr_gettype.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <pthread.h>
#include <errno.h>

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: pthread_mutexattr_gettype
 *
 * Description:
 *   Return the mutex type from the mutex attributes.
 *
 * Input Parameters:
 *   attr - The mutex attributes to query
 *   type - Location to return the mutex type
 *
 * Returned Value:
 *   0, if the mutex type was successfully return in 'type', or
 *   EINVAL, if any NULL pointers provided.
 *
 * Assumptions:
 *
 ****************************************************************************/

int pthread_mutexattr_gettype(FAR const pthread_mutexattr_t *attr,
                              FAR int *type)
{
  if (attr != NULL && type != NULL)
    {
#ifdef CONFIG_PTHREAD_MUTEX_TYPES
      *type = attr->type;
#else
      *type = PTHREAD_MUTEX_NORMAL;
#endif
      return 0;
    }

  return EINVAL;
}
