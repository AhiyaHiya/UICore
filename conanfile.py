from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout
from conan.tools.files import copy

class UICoreConan(ConanFile):
    name = "uicore"
    version = "1.0"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "src/*", "include/*", "resources/*", "CMakeLists.txt"
    generators = "CMakeDeps", "CMakeToolchain"

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        # Use the modern 'copy' method from conan.tools.files
        copy(self, "*.h", src="include", dst=f"{self.package_folder}/include")
        copy(self, "*.lib", src="lib", dst=f"{self.package_folder}/lib", keep_path=False)
        copy(self, "*.dll", src="bin", dst=f"{self.package_folder}/bin", keep_path=False)
        copy(self, "*.so", src="lib", dst=f"{self.package_folder}/lib", keep_path=False)
        copy(self, "*.dylib", src="lib", dst=f"{self.package_folder}/lib", keep_path=False)
        copy(self, "*.a", src="lib", dst=f"{self.package_folder}/lib", keep_path=False)

    def package_info(self):
        # Provide the libraries to link with
        self.cpp_info.libs = ["uicore"]

    def package_id(self):
        # Optional: Manage package ID compatibility
        self.info.requires.full_package_mode()  # Ensures full compatibility
