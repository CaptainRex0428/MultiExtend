#pragma once

#define MULTIEXTEND_DIRECTORY_CREATE(...) MultiExtend::Directory::Create(__VA_ARGS__)
#define MULTIEXTEND_DIRECTORY_WALK(...) MultiExtend::Directory::Walk(__VA_ARGS__)

#define MULTIEXTEND_DIRECTORY_VALID(...) MultiExtend::Directory::isDirectoryPathValid(__VA_ARGS__)

#define MULTIEXTEND_DIRECTORY_GET_INFO(...) MultiExtend::Directory::GetDirectoryInfo(__VA_ARGS__)
#define MULTIEXTEND_DIRECTORY_GET_PARENT(...) MultiExtend::Directory::GetParentDirectoryFromPath(__VA_ARGS__)