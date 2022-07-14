#include "pch.h"
#include "DataRow.h"

DataRow::DataRow(CString _id, CString _dateTime, CString _adcValue)
	:id(_id), dateTime(_dateTime), adcValue(_adcValue)
{
	
}


DataRow::~DataRow()
{
	
}

CString DataRow::getId() const
{
	return id;
}

void DataRow::SetId(const CString& id)
{
	this->id = id;
}

CString DataRow::getDateTime() const
{
	return dateTime;
}

void DataRow::setDateTime(const CString& date_time)
{
	dateTime = date_time;
}

CString DataRow::getAdcValue() const
{
	return adcValue;
}

void DataRow::setAdcValue(const CString& adc_value)
{
	adcValue = adc_value;
}
