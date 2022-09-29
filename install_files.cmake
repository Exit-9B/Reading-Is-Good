install(
	FILES
		"$<TARGET_FILE:${PROJECT_NAME}>"
		"$<TARGET_PDB_FILE:${PROJECT_NAME}>"
	DESTINATION "SKSE/Plugins"
)

if(NOT BUILD_SKYRIMVR)
	install(
		FILES
			"${CMAKE_CURRENT_SOURCE_DIR}/dist/SkyrimSE/${PROJECT_NAME}.esp"
		DESTINATION "."
	)
else()
	install(
		FILES
			"${CMAKE_CURRENT_SOURCE_DIR}/dist/SkyrimVR/${PROJECT_NAME}.esp"
		DESTINATION "."
	)
endif()

install(
	FILES
		"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.bsa"
	DESTINATION "."
)

install(
	FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/dist/Data/MCM/Config/${PROJECT_NAME}/settings.ini"
	DESTINATION
		"MCM/Config/${PROJECT_NAME}"
)

install(
	FILES ${Papyrus_SOURCES}
	DESTINATION "Source/Scripts"
)
