#include "monoutil.h"
#include "../bbruntime/bbbank.h"

PUBLIC_METHOD bbBank* CreateBank_internal(int size)
{
	return bbCreateBank(size);
}

PUBLIC_METHOD void FreeBank_internal(bbBank* bank)
{
	bbFreeBank(bank);
}

PUBLIC_METHOD int BankSize_internal(bbBank* bank)
{
	return bbBankSize(bank);
}

PUBLIC_METHOD void ResizeBank_internal(bbBank* bank, int size)
{
	bbResizeBank(bank, size);
}

PUBLIC_METHOD void CopyBank_internal(bbBank* src, int srcOffset, bbBank* dest, int destOffset, int count)
{
	bbCopyBank(src, srcOffset, dest, destOffset, count);
}

PUBLIC_METHOD char PeekByte_internal(bbBank* bank, int offset)
{
	return (char)bbPeekByte(bank, offset);
}

PUBLIC_METHOD short PeekShort_internal(bbBank* bank, int offset)
{
	return (short)bbPeekShort(bank, offset);
}

PUBLIC_METHOD int PeekInt_internal(bbBank* bank, int offset)
{
	return bbPeekInt(bank, offset);
}

PUBLIC_METHOD float PeekFloat_internal(bbBank* bank, int offset)
{
	return bbPeekFloat(bank, offset);
}

PUBLIC_METHOD void PokeByte_internal(bbBank* bank, int offset, char value)
{
	bbPokeByte(bank, offset, value);
}

PUBLIC_METHOD void PokeShort_internal(bbBank* bank, int offset, short value)
{
	bbPokeShort(bank, offset, value);
}

PUBLIC_METHOD void PokeInt_internal(bbBank* bank, int offset, int value)
{
	bbPokeInt(bank, offset, value);
}

PUBLIC_METHOD void PokeFloat_internal(bbBank* bank, int offset, float value)
{
	bbPokeFloat(bank, offset, value);
}

PUBLIC_METHOD int ReadBytes_internal(bbBank* bank, bbStream* stream, int offset, int count)
{
	return bbReadBytes(bank, stream, offset, count);
}

PUBLIC_METHOD int WriteBytes_internal(bbBank* bank, bbStream* stream, int offset, int count)
{
	return bbWriteBytes(bank, stream, offset, count);
}