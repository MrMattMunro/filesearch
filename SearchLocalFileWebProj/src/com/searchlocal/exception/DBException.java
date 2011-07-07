package com.searchlocal.exception;

/**
 * 
 * @author Ketu Ri
 * @version $Revision 1.0$
 */
public class DBException extends Exception {

	/** serialVersionUID */
	private static final long serialVersionUID = 1L;

	private String messageKey;

	private Object[] params;

	/**
	 * 
	 */
	public DBException(String messageKey, String param1) {
		super("DBException");
		this.messageKey = messageKey;
		this.params = new Object[] { param1 };
	}

	public DBException(String messageKey, String param1, String param2) {
		super("DBException");
		this.messageKey = messageKey;
		this.params = new Object[] { param1, param2 };
	}

	public DBException(String messageKey, Object[] params) {
		this.messageKey = messageKey;
		this.params = params;
	}

	public DBException(String messageKey, Throwable cause) {
		super(messageKey, cause);
		this.messageKey = messageKey;
	}

	public DBException(String messageKey) {
		//super(messageKey);
		this.messageKey = messageKey;
	}

	public Object[] getParams() {
		return this.params;
	}

	public String getMessageKey() {
		return this.messageKey;
	}
}
