/*
 * Variable.h
 *
 *  Created on: Mar 26, 2012
 *      Author: Cuneyt AY
 */

#ifndef VARIABLE_H_
#define VARIABLE_H_

#include <string>
#include "znm-core_global.h"

class ZNMCORESHARED_EXPORT Variable
{
public:
    Variable(double* pAddr, const std::string& pName, const std::string& pDesc, unsigned int pRow, unsigned int pCol);

	virtual ~Variable();

	/**
	 * Returns variable's name
	 * @return variable's name
	 */
	inline std::string name(){ return mName; }

	/**
	 * Sets description
	 * @param pDesc new description
	 */
	void setDescription (const std::string& pDesc) { mDescription = pDesc; }

	/**
	 * Gets description
	 * @return description
	 */
	inline std::string description(){ return mDescription; }

	/**
	 * Gets variable's size
	 * @return size
	 */
    inline unsigned int size(){ return row() * col(); }

	/**
	 * Gets variable's row
	 * @return row
	 */
    inline unsigned int row(){ return mRow; }

	/**
	 * Gets variable's col
	 * @return col
	 */
    inline unsigned int col(){ return mCol; }

protected:

	/** Degisken adresi */
	double* mVariableAddr;

	/** Degisken ismi */
	std::string mName;

	/** Degisken tanimi */
	std::string mDescription;

	/** Degisken satir sayisi */
    unsigned int mRow;

	/** Degisken sutun sayisi */
    unsigned int mCol;
};

#endif /* VARIABLE_H_ */
