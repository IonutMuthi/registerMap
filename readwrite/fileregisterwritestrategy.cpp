#include "fileregisterwritestrategy.hpp"

FileRegisterWriteStrategy::FileRegisterWriteStrategy(QString path)
	:path(path)
{

}

void FileRegisterWriteStrategy::write(uint32_t address, uint32_t val)
{
 //TODO HOW SHOULD WE TREAT WRITE ?
}
