#pragma once
class DataRow
{
private:
	CString id;
	CString dateTime;
	CString adcValue;

public:
	DataRow(CString _id, CString _dateTime, CString _adcValue);
	~DataRow();

	CString getId() const;
	void SetId(const CString& id);
	CString getDateTime() const;
	void setDateTime(const CString& date_time);
	CString getAdcValue() const;
	void setAdcValue(const CString& adc_value);

};

