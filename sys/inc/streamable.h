#pragma once

#define DECL_FORMAT(type, name) inline std::ostream& operator<<(std::ostream& os, const type& name)
