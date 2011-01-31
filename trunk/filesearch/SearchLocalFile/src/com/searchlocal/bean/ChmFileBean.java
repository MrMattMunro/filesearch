/**
 * $RCSfile: ChmFileBean.java
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
 * chm文件
 * 
 * <p>Title: chm文件</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class ChmFileBean extends BaseFileBean {

	/** 标签名称 */
	private String catalogname;

	/**
	 * @return Returns the catalogname.
	 */
	public String getCatalogname() {
		return catalogname;
	}

	/**
	 * @param catalogname The catalogname to set.
	 */
	public void setCatalogname(String catalogname) {
		this.catalogname = catalogname;
	}

}
