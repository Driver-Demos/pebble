/*
 * Copyright 2024 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "task_init.h"

#include "drivers/rng.h"
#include "drivers/rtc.h"

#include <stdlib.h>

void task_init(void) {
  uint32_t seed;
  if (!rng_rand(&seed)) {
    // Fallback, time XOR'd with an approximation of the current stack pointer:
    seed = rtc_get_time() ^ (uintptr_t) &seed;
  }
  srand(seed);
}
