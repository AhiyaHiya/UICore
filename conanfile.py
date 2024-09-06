from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout

class UICoreConan(ConanFile):
    name = "UICore"
    version = "1.0"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "src/*", "include/*", "CMakeLists.txt"
    generators = "CMakeDeps", "CMakeToolchain"

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", src="include")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["UICore"]

