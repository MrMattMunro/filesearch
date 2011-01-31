/**
 * $RCSfile: TxtFileBean.java
 * $Revision: 1.0
 * $Date: Jan 19, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.bean;

/**
 * 文本文件，包括代码
 * 
 * <p>Title: 文本文件，包括代码</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class TxtFileBean extends BaseFileBean {

	/** 行数 */
	private int rownb;

	/**
	 * @return Returns the rownb.
	 */
	public int getRownb() {
		return rownb;
	}

	/**
	 * @param rownb
	 *            The rownb to set.
	 */
	public void setRownb(int rownb) {
		this.rownb = rownb;
	}

}
