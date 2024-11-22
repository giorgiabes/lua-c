#include <stdio.h>
#include "../lib/lua/src/lua.h"
#include "../lib/lua/src/lualib.h"
#include "../lib/lua/src/lauxlib.h"

void lua_example_dofile(void) {
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	luaL_dofile(L, "./scripts/factorial.lua");
	lua_close(L);
}

void lua_example_getvar(void) {
	lua_State* L = luaL_newstate();
	luaL_dostring(L, "some_var = 486");
	lua_getglobal(L, "some_var");
	lua_Number some_var_in_c = lua_tonumber(L, -1);

	printf("The value of some_var inside C is: %d\n", (int) some_var_in_c);

	lua_close(L);
}

void lua_example_stack(void) {
	lua_State* L = luaL_newstate();

	lua_pushnumber(L, 286); // stack[1] or [-3]
	lua_pushnumber(L, 386); // stack[2] or [-2]
	lua_pushnumber(L, 486); // stack[3] or [-1]
	
	lua_Number element;
	element = lua_tonumber(L, -1);
	printf("The last added element in position 3 of the stack is %d\n", (int) element);

	lua_remove(L, 2); // this should remove 386 from the stack
	element = lua_tonumber(L, 2);
	printf("Position 2 of the stack is now: %d\n", (int) element);

	lua_close(L);
}

void lua_example_call_lua_function(void) {
	lua_State* L = luaL_newstate();
	luaL_dofile(L, "./scripts/pythagoras.lua");
	lua_getglobal(L, "pythagoras");
	if (lua_isfunction(L, -1)) {
		lua_pushnumber(L, 3); // first function argument, a
		lua_pushnumber(L, 4); // second function argument, b
		const int NUM_ARGS = 2;
		const int NUM_RETURNS = 1;
		lua_pcall(L, NUM_ARGS, NUM_RETURNS, 0);

		lua_Number pythagoras_result = lua_tonumber(L, -1);

		printf("The Pythagoras(3,4) is %f\n", (float) pythagoras_result);
	}
	lua_close(L);
}


int main(int argc, char *argv[]) {
	// lua_example_dofile();
	// lua_example_getvar();
	// lua_example_stack();
	lua_example_call_lua_function();
	return 0;
}
