hook.so: hook.c
	gcc -Wall -shared -ldl -linput -fPIC $< -o $@
