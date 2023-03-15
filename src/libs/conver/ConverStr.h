#ifndef CONVERSTR_H_H_HEAD__FILE__
#define CONVERSTR_H_H_HEAD__FILE__
#pragma once

#include "Conver_export.h"
#include <string>
#include <QString>

namespace strConver {
	
	/// @brief 把一个字符串转换到基于运行时的标准的 C++ 字符串
	/// @param inStr 字符串
	/// @return 标准的字符串
	inline std::string CONVER_EXPORT converStdStr( const QString &inStr ) {
		return inStr.toLocal8Bit().toStdString();
	}
};


#endif // CONVERSTR_H_H_HEAD__FILE__