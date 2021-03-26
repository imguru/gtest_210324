#ifndef DLOGGERTARGET_H
#define DLOGGERTARGET_H

struct DLoggerTarget {
	virtual ~DLoggerTarget() {};

	virtual void Write(Level level, const std::string& message) = 0;
};

#endif
