package com.searchlocal.bean;

/**
 * 消息Bean
 * 
 * <p>Title: 消息Bean</p>
 * <p>Description: </p>
 * <p>site: www.slfile.com</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class MessageBean {
	
	/** 消息类型 */
	private String msgtype;

	/** 消息代码 */
	private String msgcode;
	
	/** 消息内容 */
	private String msgcontent;
	
	/** 消息参数 */
	private String[] params;
	
	public MessageBean(String msgType, String msgcode, String msgcontent, String[] param){
		this.msgtype = msgType;
		this.msgcode = msgcode;
		this.msgcontent = msgcontent;
		this.params = param;
	}

	public String[] getParams() {
		return params;
	}

	public void setParams(String[] params) {
		this.params = params;
	}

	public String getMsgcode() {
		return msgcode;
	}

	public void setMsgcode(String msgcode) {
		this.msgcode = msgcode;
	}

	public String getMsgtype() {
		return msgtype;
	}

	public void setMsgtype(String msgtype) {
		this.msgtype = msgtype;
	}

	public String getMsgcontent() {
		return msgcontent;
	}

	public void setMsgcontent(String msgcontent) {
		this.msgcontent = msgcontent;
	}
	
}
