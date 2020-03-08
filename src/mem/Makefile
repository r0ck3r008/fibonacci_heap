all: alloc_obj node_obj heap_obj hmap_objs

alloc_obj:
	make -C alloc/

node_obj:
	make -C node/

heap_obj:
	make -C heap/

hmap_objs:
	make -C hmap/

clean:
	make -C alloc clean
	make -C node clean
	make -C heap clean
	make -C hmap clean
