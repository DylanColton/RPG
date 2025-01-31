#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <filesystem>
#include <cstdlib>
#include <string>

namespace fs = std::filesystem;

class Filesystem {
	private:
		typedef std::string (*Builder) (const std::string& path);

	public:
		static std::string getPath(const std::string& path) {
			static std::string(*pathBuilder)(std::string const &) = getPathBuilder();
			return (*pathBuilder)(path);
		}

	private:
		static fs::path findProjRoot() {
			fs::path current = fs::current_path();

			while (current.has_parent_path()) {
				if (fs::exists(current / "main"))
					return current;
				current = current.parent_path();
			}
			throw std::runtime_error("Project root not found: 'main' file missing in any parent directory");
		}
		
		static std::string const getRoot() {
			static fs::path envRoot = Filesystem::findProjRoot();
			return envRoot.string();
		}

		static Builder getPathBuilder() {
			if (getRoot() != "")
				return &Filesystem::getPathRelativeRoot;
			else
				return &Filesystem::getPathRelativeBinary;
		}

		static std::string getPathRelativeRoot(const std::string& path) {
			return getRoot() + std::string("/") + path;
		}

		static std::string getPathRelativeBinary(const std::string& path) {
			return "../../" + path;
		}
};

#endif
