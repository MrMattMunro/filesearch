/**
 * $RCSfile: MessageParam.java
 * $Revision: 1.0
 * $Date: Jan 30, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.param;

/**
 * 显示消息对应的Message
 * 
 * <p>Title: 显示消息对应的Message</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class MessageParam {

	/**  参数 */
	private String param;

	/**  文本Label */
	private String label;

	/**  
	 * 构造器
     */
	public MessageParam(String param, String label) {
		this.param = param;
		this.label = label;
	}

	/**
	 * 取得param
	 * 
	 * @return String param 
	 */
	public String getParam() {
		return param;
	}

	/**
	 * 设定param 
	 * 
	 * @param String param 
	 */
	public void setParam(String param) {
		this.param = param;
	}

	/**
	 * 取得label
	 * 
	 * @return String label 
	 */
	public String getLabel() {
		return label;
	}

	/**
	 * 设定label 
	 * 
	 * @param String label 
	 */
	public void setLabel(String label) {
		this.label = label;
	}

}
