/*
 *  Copyright 2014 The Luvit Authors. All Rights Reserved.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */
#include "luv.h"

static void async_cb(uv_async_t* handle) {
  lua_State* L = (lua_State*)handle->data;
  luv_find_async(L, handle);
  luv_emit_event(L, "onasync", 1);
}

static int new_async(lua_State* L) {
  uv_loop_t* loop = luv_check_loop(L, 1);
  uv_async_t* handle = luv_create_async(L);
  int ret;
  handle->data = L;
  ret = uv_async_init(loop, handle, async_cb);
  if (ret < 0) return luv_error(L, ret);
  return 1;
}

static int luv_async_send(lua_State* L) {
  uv_async_t* handle = luv_check_async(L, 1);
  int ret = uv_async_send(handle);
  if (ret < 0) return luv_error(L, ret);
  lua_pushinteger(L, ret);
  return 1;
}