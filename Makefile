# Helper Makefile to make things easier.

format:
	find src -name "*.cpp" | xargs clang-format -i
	find inc -name "*.hpp" | xargs clang-format -i
