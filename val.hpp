#pragma once

#include <cstring>

namespace mnem {

typedef enum {
	INT,
	STRING,
	BOOL,
	LIST,
	MAP,
} ValType;

struct ValStr {
	size_t len;
	const char* bytes;
};

struct Val {
	ValType type;
	union {
		int64_t i;
		ValStr s;
	} u;

	static Val i(int64_t i) {
		Val retval { ValType::INT, { i } };
		return retval;
	}

	static Val s(const char* s) {
		size_t len = strlen(s);
		char* mbytes = (char*) calloc(len, 1);
		memcpy(mbytes, s, len);
		const char* bytes = mbytes;
		Val retval { .type{ ValType::STRING }, .u{ .s{ .len{len}, .bytes{bytes} } } };
		return retval;
	}

	~Val() {
		if (type == ValType::STRING) { free((void*)u.s.bytes); }
	}
};

}

