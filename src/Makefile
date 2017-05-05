all: server client
	
server:
	make -f makefile.server

client:
	make -f makefile.client

clean:
	rm -f libcrest/libcrest.a libserver/libserver.a run_crest/run_crest_server run_crest/run_crest_client
	rm -f process_cfg/process_cfg tools/print_execution
	rm -f */*.o */*~ *~