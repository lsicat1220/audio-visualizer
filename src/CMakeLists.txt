add_library(logic STATIC
	./fft.c
	./complex.c
	./audio.c
)		

target_link_libraries(logic PRIVATE m)
target_link_libraries(logic PRIVATE SDL3::SDL3)

#add_executable(main ./main.c)

#target_link_libraries(main PRIVATE logic)
