
set(LibGit2_Spec_URL "https://github.com/libgit2/libgit2/archive/v0.26.8.tar.gz")
set(LibGit2_Spec_ArchiveName libgit2-v0.26.8.tar.gz)
set(LibGit2_Spec_ArchiveSha256 0f20d7e239be030db33d7350bab38ada2830b3bffab5539730074e71b0267796)

set(LibGit2_Spec_MacLibraries libgit2.0.26.8.dylib)
set(LibGit2_Spec_MacLibrariesSymlinks libgit2*.dylib)
set(LibGit2_Spec_LinuxLibraries libgit2.so.0.26.8)
set(LibGit2_Spec_LinuxLibrariesSymlinks libgit2.so*)
set(LibGit2_Spec_WindowsDLLs libgit2.dll)

set(OpenSSL_EscapedLibrariesNames)
foreach(lib ${OpenSSL_FullLibrariesPaths})
    if(OpenSSL_EscapedLibrariesNames)
        set(OpenSSL_EscapedLibrariesNames "${OpenSSL_EscapedLibrariesNames}$<SEMICOLON>${lib}")
    else()
        set(OpenSSL_EscapedLibrariesNames "${lib}")
    endif()
endforeach()

set(LibGit2_Spec_CMAKE_ARGS
    -DBUILD_CLAR=OFF -DUSE_SSH=ON
    -DOPENSSL_FOUND=ON
    "-DOPENSSL_INCLUDE_DIR=${ThirdPartyCacheInstallInclude}"
    -DOPENSSL_LIBRARY_DIR=${ThirdPartyCacheInstallLib}
    "-DOPENSSL_LIBRARIES=${OpenSSL_EscapedLibrariesNames}"

    -DLIBSSH2_FOUND=ON
    "-DLIBSSH2_INCLUDE_DIRS=${ThirdPartyCacheInstallInclude}"
    "-DLIBSSH2_LIBRARIES=${LibSSH2_FullLibrariesPaths}"
)

add_thirdparty_with_cmake(LibGit2
    DOWNLOAD_URL ${LibGit2_Spec_URL}
    ARCHIVE_NAME ${LibGit2_Spec_ArchiveName}
    ARCHIVE_SHA256 ${LibGit2_Spec_ArchiveSha256}
    CMAKE_EXTRA_ARGS ${LibGit2_Spec_CMAKE_ARGS}
    MAC_LIBRARIES ${LibGit2_Spec_MacLibraries}
    MAC_LIBRARIES_SYMLINK_PATTERNS ${LibGit2_Spec_MacLibrariesSymlinks}
    LINUX_LIBRARIES ${LibGit2_Spec_LinuxLibraries}
    LINUX_LIBRARIES_SYMLINK_PATTERNS ${LibGit2_Spec_LinuxLibrariesSymlinks}
    WINDOWS_DLLS ${LibGit2_Spec_WindowsDLLs}
    DEPENDENCIES ${LibSSH2_BuildDep}
    NEVER_LOG_CONFIGURE
)
