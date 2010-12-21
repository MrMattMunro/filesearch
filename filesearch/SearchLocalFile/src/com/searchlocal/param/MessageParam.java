package com.searchlocal.param;

public class MessageParam {

	private String param;

	private String label;

	public MessageParam(String param,String label){
		this.param = param;
		this.label = label;
	}
	
	/**
	 * @return Returns the label.
	 */
	public String getLabel() {
		return label;
	}

	/**
	 * @param label
	 *            The label to set.
	 */
	public void setLabel(String label) {
		this.label = label;
	}

	/**
	 * @return Returns the param.
	 */
	public String getParam() {
		return param;
	}

	/**
	 * @param param
	 *            The param to set.
	 */
	public void setParam(String param) {
		this.param = param;
	}

}
