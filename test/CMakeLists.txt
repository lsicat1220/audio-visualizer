set(list
	fft_test
	complex_test
	wav_test
	bitreverse_test
	fft_stress_test
	visual_test
)

foreach(file IN LISTS list)
	add_executable(${file} ./${file}.c)
	target_include_directories(${file} PRIVATE ../src/)
	target_link_libraries(${file} PRIVATE logic)
endforeach()
