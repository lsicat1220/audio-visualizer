add_library(logic STATIC
	./fft.c
	./complex.c
	./audio.c
)		

target_link_libraries(logic PRIVATE m)

#add_executable(main ./main.c)

#target_link_libraries(main PRIVATE logic)
