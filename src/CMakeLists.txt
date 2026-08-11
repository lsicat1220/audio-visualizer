add_library(logic STATIC
	./fft.c
	./complex.c
	./wav.c
)		

target_link_libraries(logic PRIVATE m)

#add_executable(main ./main.c)

#target_link_libraries(main PRIVATE logic)
