package com.web.searchlocal.exception;


public class LogicException extends Exception {

	/** serialVersionUID */
	private static final long serialVersionUID = 1L;

	private String messageKey;

	private Object[] params;

	public LogicException(String messageKey, String param1) {
		super("LogicException");
		this.messageKey = messageKey;
		this.params = new Object[] { param1 };
	}
	
	public LogicException(String messageKey, String param1, String param2) {
		super("LogicException");
		this.messageKey = messageKey;
		this.params = new Object[] { param1, param2 };
	}

	public LogicException(String messageKey, Object[] params) {
		this.messageKey = messageKey;
		this.params = params;
	}

	public LogicException(String messageKey, Throwable cause) {
		super(messageKey, cause);
		this.messageKey = messageKey;
	}

	public LogicException(String messageKey) {
		// super(messageKey);
		this.messageKey = messageKey;
	}
	
	public Object[] getParams() {
		return this.params;
	}

	public String getMessageKey() {
		return this.messageKey;
	}
}
