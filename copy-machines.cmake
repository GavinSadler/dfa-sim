
# Get a list of all files ending in .dfa and .in
file (GLOB files ${CMAKE_CURRENT_LIST_DIR}/*.dfa ${CMAKE_CURRENT_LIST_DIR}/*.in)

# Copy the files to the build directory
file (COPY ${files} DESTINATION ${CMAKE_CURRENT_BINARY_DIR} NO_SOURCE_PERMISSIONS)
