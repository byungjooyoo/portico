/*
 *   Copyright 2012 The Portico Project
 *
 *   This file is part of portico.
 *
 *   portico is free software; you can redistribute it and/or modify
 *   it under the terms of the Common Developer and Distribution License (CDDL)
 *   as published by Sun Microsystems. For more information see the LICENSE file.
 *
 *   Use of this software is strictly AT YOUR OWN RISK!!!
 *   If something bad happens you do not have permission to come crying to me.
 *   (that goes for your lawyer as well)
 *
 */
#include "common.h"
#include "types/encoding/BitHelpers.h"
#include "types/encoding/basic/BasicTypeImpl.h"
#include "RTI/encoding/BasicDataElements.h"

IEEE1516E_NS_START

DEFINE_BASIC_TYPE_IMPL( HLAfloat32LEImplementation, float )

//------------------------------------------------------------------------------------------
//                                       CONSTRUCTORS                                       
//------------------------------------------------------------------------------------------
// Constructor: Default
// Uses internal memory.
HLAfloat32LE::HLAfloat32LE()
{
	this->_impl = new HLAfloat32LEImplementation( 0.0f );
}

// Constructor: Initial Value
// Uses internal memory.
HLAfloat32LE::HLAfloat32LE( const float& inData )
{
	this->_impl = new HLAfloat32LEImplementation( inData );
}

// Constructor: External memory
// This instance changes or is changed by contents of external memory.
// Caller is responsible for ensuring that the external memory is
// valid for the lifetime of this object or until this object acquires
// new memory through setDataPointer.
// A null value will construct instance to use internal memory.
HLAfloat32LE::HLAfloat32LE( float* inData )
{
	this->_impl = new HLAfloat32LEImplementation( inData );
}

// Constructor: Copy
// Uses internal memory.
HLAfloat32LE::HLAfloat32LE( const HLAfloat32LE& rhs )
{
	this->_impl = new HLAfloat32LEImplementation( rhs.get() );
}

HLAfloat32LE::~HLAfloat32LE()
{
	delete this->_impl;
}

//------------------------------------------------------------------------------------------
//                                     INSTANCE METHODS
//------------------------------------------------------------------------------------------
// Return a new copy of the DataElement
// Copy uses internal memory.
std::auto_ptr<DataElement> HLAfloat32LE::clone() const
{
	return std::auto_ptr<DataElement>( new HLAfloat32LE(*this) );
}

// Encode this element into a new VariableLengthData
VariableLengthData HLAfloat32LE::encode() const
	throw( EncoderException )
{
	VariableLengthData data;
	this->encode( data );

	return data;
}

// Encode this element into an existing VariableLengthData
void HLAfloat32LE::encode( VariableLengthData& inData ) const
	throw( EncoderException )
{
	// Assign a buffer to take the float
	char buffer[BitHelpers::LENGTH_FLOAT];
	BitHelpers::encodeFloatLE( this->get(), buffer, 0 );
	
	inData.setData( buffer, BitHelpers::LENGTH_FLOAT );
}

// Encode this element and append it to a buffer
void HLAfloat32LE::encodeInto( std::vector<Octet>& buffer ) const
	throw( EncoderException )
{
	char data[BitHelpers::LENGTH_FLOAT];
	BitHelpers::encodeFloatLE( this->get(), data, 0 );

	buffer.insert( buffer.end(), data, data + BitHelpers::LENGTH_FLOAT );
}

// Decode this element from the RTI's VariableLengthData.
void HLAfloat32LE::decode( const VariableLengthData& inData )
	throw( EncoderException )
{
	if( inData.size() < BitHelpers::LENGTH_FLOAT )
		throw EncoderException( L"Insufficient data in buffer to decode value" );

	float value = BitHelpers::decodeFloatLE( (const char*)inData.data(), 0 );
	this->set( value );
}

// Decode this element starting at the index in the provided buffer
// Return the index immediately after the decoded data.
size_t HLAfloat32LE::decodeFrom( const std::vector<Octet>& buffer, size_t index )
	throw( EncoderException )
{
	float value = BitHelpers::decodeFloatLE( buffer, index );
	this->set( value );
	return index + BitHelpers::LENGTH_FLOAT;
}

// Return the size in bytes of this element's encoding.
size_t HLAfloat32LE::getEncodedLength() const
	throw( EncoderException )
{
	return BitHelpers::LENGTH_FLOAT;
}

// Return the octet boundary of this element.
unsigned int HLAfloat32LE::getOctetBoundary() const
{
	return BitHelpers::LENGTH_FLOAT;
}

// Return a hash of the encoded data
// Provides mechanism to map DataElement discriminants to variants
// in VariantRecord.
Integer64 HLAfloat32LE::hash() const
{
	// recast value as an int
	float value = this->get();
	int asInt = *((int*)&value);

	return 31 * 7 + asInt;
}

// Change this instance to use supplied external memory.
// Caller is responsible for ensuring that the external memory is
// valid for the lifetime of this object or until this object acquires
// new memory through this call.
// Null pointer results in an exception.
void HLAfloat32LE::setDataPointer( float* inData )
	throw( EncoderException )
{
	this->_impl->setUseExternalMemory( inData );
}

// Set the value to be encoded.
// If this element uses external memory, the memory will be modified.
void HLAfloat32LE::set( float inData )
{
	this->_impl->setValue( inData );
}

// Get the value from encoded data.
float HLAfloat32LE::get() const
{
	return this->_impl->getValue();
}

//------------------------------------------------------------------------------------------
//                                    OPERATOR OVERLOADS
//------------------------------------------------------------------------------------------
// Assignment Operator
// Uses existing memory of this instance.
HLAfloat32LE& HLAfloat32LE::operator= ( const HLAfloat32LE& rhs )
{
	this->_impl->setUseInternalMemory( rhs.get() );
	return *this;
}

// Assignment of the value to be encoded data.
// If this element uses external memory, the memory will be modified.
HLAfloat32LE& HLAfloat32LE::operator= ( float rhs )
{
	this->set( rhs );
	return *this;
}

// Conversion operator to float
// Return value from encoded data.
HLAfloat32LE::operator float() const
{
	return this->get();
}

//------------------------------------------------------------------------------------------
//                                      STATIC METHODS
//------------------------------------------------------------------------------------------

IEEE1516E_NS_END
