all: alloc_objs node_objs heap_objs

alloc_objs:
	make -C alloc/

node_objs:
	make -C node/

heap_objs:
	make -C heap/

clean:
	make -C alloc/ clean
	make -C node/ clean
	make -C heap/ clean
