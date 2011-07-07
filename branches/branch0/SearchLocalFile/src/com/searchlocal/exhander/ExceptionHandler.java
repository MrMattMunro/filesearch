package com.searchlocal.exhander;

import java.util.ArrayList;
import java.util.List;

import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.util.CLogger;
import com.searchlocal.util.MessageUtil;

public class ExceptionHandler {

	private static CLogger logger = new CLogger(ExceptionHandler.class);

	private static List<String> errorList = new ArrayList<String>();

	public static String getMsg(Exception ex) {

		String messkey = "";
		Object[] params = null;
		if (ex instanceof DBException) {
			DBException exp = (DBException) ex;
			messkey = exp.getMessageKey();
			params = exp.getParams();

		} else if (ex instanceof LogicException) {
			DBException exp = (DBException) ex;
			messkey = exp.getMessageKey();
			params = exp.getParams();
		}
		StringBuffer bf = new StringBuffer();
		String message = MessageUtil.getMsgbyId(messkey);
		bf.append(message);
		if (null != params) {
			for (int i = 0; i < params.length; i++) {
				bf.append((String) params[i]);
			}
		}
		errorList.add(bf.toString());
		logger.error(bf.toString());
		return bf.toString();
	}

	/**
	 * @return Returns the errorList.
	 */
	public static List<String> getErrorList() {
		return errorList;
	}

	/**
	 * @param errorList
	 *            The errorList to set.
	 */
	public static void setErrorList(List<String> errorList) {
		ExceptionHandler.errorList = errorList;
	}
}
