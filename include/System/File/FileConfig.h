#pragma once

#define MULTIEXTEND_TAG_FILESYSTEM_TYPE_NOTFOUND std::filesystem::file_type::not_found
#define MULTIEXTEND_TAG_FILESYSTEM_TYPE_DIRECTORY std::filesystem::file_type::directory
#define MULTIEXTEND_TAG_FILESYSTEM_TYPE_FILE std::filesystem::file_type::regular

#define MULTIEXTEND_FILESYSTEM std::filesystem

#define MULTIEXTEND_PATTERN_PATH_NEXIST_ERROR "Path (\"{0}\") doesn't exist.[{1}]"
#define MULTIEXTEND_PATTERN_FILE_OPEN_FAILED "File (\"{0}\") open failed.[{1}]"
#define MULTIEXTEND_PATTERN_FILE_PATH_NULL "File path is empty.[{0}]"
#define MULTIEXTEND_PATTERN_FILE_FOLDER_CREATED "Directory (\"{0}\") created.[{1}]"
#define MULTIEXTEND_PATTERN_FILE_RESET_TIP "File (\"{0}\") has been reset.[{1}]"
#define MULTIEXTEND_PATTERN_FILE_REOPEN_WARN "File (\"{0}\") reopened.[{1}]"

#define MULTIEXTEND_PATTERN_FILE_FOLDER_PATH_NEXIST_ERROR "File parent directory (\"{0}\") doesn't exist.[{1}]"
#define MULTIEXTEND_PATTERN_FILE_OBJ_NINIT_ERROR "File object (\"{0}\") hasn't been initialized.[{1}]"
#define MULTIEXTEND_PATTERN_FILE_CREATED_TIP "Created file (\"{0}\").[{1}]"

#define MULTIEXTEND_GET_FILE_NAME_SUBFIX

#define MULTIEXTEND_TAG_FILE_DEFAULT_MODE std::ios::in | std::ios::out | std::ios::app
#define MULTIEXTEND_TAG_FILE_CLEAR_MODE std::ios::out | std::ios::trunc
#define MULTIEXTEND_TAG_FILE_GET_MODE std::ios::in

#define MULTIEXTEND_DEFAULT_FILECREATE_DELAY_MS 2000


