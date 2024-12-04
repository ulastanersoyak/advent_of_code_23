function(normalize_day_number INPUT OUTPUT)
  if(INPUT LESS 10)
    set(${OUTPUT}
        "0${INPUT}"
        PARENT_SCOPE)
  else()
    set(${OUTPUT}
        "${INPUT}"
        PARENT_SCOPE)
  endif()
endfunction()

# process each year
foreach(YEAR RANGE 2015 2024)
  message(STATUS "Processing year ${YEAR}")
  set(YEAR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${YEAR}")

  # check if year directory exists
  if(NOT EXISTS ${YEAR_DIR})
    message(STATUS "Directory for year ${YEAR} not found, skipping")
    continue()
  endif() # Changed from } to endif()

  # find all day directories
  file(GLOB DAYS "${YEAR_DIR}/day[0-9]*")
  list(SORT DAYS)

  foreach(DAY ${DAYS})
    # extract day number
    string(REGEX MATCH "day([0-9]+)$" DAY_MATCH "${DAY}")
    if(NOT DAY_MATCH)
      message(WARNING "Invalid day directory format: ${DAY}")
      continue()
    endif()

    set(DAY_NUMBER ${CMAKE_MATCH_1})
    normalize_day_number(${DAY_NUMBER} PADDED_DAY)
    message(STATUS "  Processing day ${PADDED_DAY}")

    # find all CPP files for the day
    file(GLOB CPP_FILES "${DAY}/*.cpp")
    if(NOT CPP_FILES)
      message(STATUS "    No C++ files found in ${DAY}")
      continue()
    endif()

    foreach(CPP_FILE ${CPP_FILES})
      # extract part number
      string(REGEX MATCH "p([0-9]+)" PART_MATCH "${CPP_FILE}")
      if(NOT PART_MATCH)
        message(WARNING "    Invalid part format in file: ${CPP_FILE}")
        continue()
      endif()
      set(PART_NUMBER ${CMAKE_MATCH_1})

      # create target name in format: aoc_YYYY_DD_PX
      set(TARGET_NAME "aoc_${YEAR}_${PADDED_DAY}_p${PART_NUMBER}")
      message(STATUS "    Adding target: ${TARGET_NAME}")

      # add executable target
      add_executable(${TARGET_NAME} ${CPP_FILE})

      # set output directory to bin/YYYY/
      set_target_properties(
        ${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                  "${CMAKE_BINARY_DIR}/bin/${YEAR}")

      # add any common compile definitions or options if needed
      target_compile_definitions(
        ${TARGET_NAME} PRIVATE AOC_YEAR=${YEAR} AOC_DAY=${DAY_NUMBER}
                               AOC_PART=${PART_NUMBER})
    endforeach()
  endforeach()
endforeach()
