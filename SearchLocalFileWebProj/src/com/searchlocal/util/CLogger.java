package com.searchlocal.util;

import java.io.File;

import org.apache.log4j.Logger;
import org.apache.log4j.xml.DOMConfigurator;

import com.searchlocal.constants.Constant;
import com.searchlocal.exception.LogicException;

public class CLogger {

	private Logger logger;

	/**
	 * @return Returns the logger.
	 */
	public Logger getLogger() {
		return logger;
	}

	public CLogger(Class classz) {
		initLogger();
		logger = Logger.getLogger(classz);
	}

	public void error(String strMsgID) {
		String[] strParams = null;
		error(strMsgID, strParams, null);
	}

	public void error(String strMsgID, String strParam1) {
		String[] strParams = new String[1];
		strParams[0] = strParam1;
		error(strMsgID, strParams, null);
	}

	public void error(String strMsgID, String strParam1, String strParam2) {
		String[] strParams = new String[2];
		strParams[0] = strParam1;
		strParams[1] = strParam2;
		error(strMsgID, strParams, null);
	}

	public void error(String strMsgID, String[] strParams) {
		error(strMsgID, strParams, null);
	}

	public void error(String strMsgID, Exception e) {
		String[] strParams = null;
		error(strMsgID, strParams, e);
	}

	public void error(String strMsgID, String strParam1, Exception e) {
		String[] strParams = new String[1];
		strParams[0] = strParam1;
		error(strMsgID, strParams, e);
	}

	public void error(String strMsgID, String strParam1, String strParam2,
			Exception e) {
		String[] strParams = new String[2];
		strParams[0] = strParam1;
		strParams[1] = strParam2;
		error(strMsgID, strParams, e);
	}

	public void error(String strMsgID, String[] strParams, Exception e) {
		String strMsg = getForamtedMsg(strMsgID, strParams);
		if (e == null) {
			logger.error(strMsg);
		} else {
			logger.error(strMsg, e);
		}
	}

	public void warn(String strMsgID) {
		String[] strParams = null;
		warn(strMsgID, strParams, null);
	}

	public void warn(String strMsgID, String strParam1) {
		String[] strParams = new String[1];
		strParams[0] = strParam1;
		warn(strMsgID, strParams, null);
	}

	public void warn(String strMsgID, String strParam1, String strParam2) {
		String[] strParams = new String[2];
		strParams[0] = strParam1;
		strParams[1] = strParam2;
		warn(strMsgID, strParams, null);
	}

	public void warn(String strMsgID, String[] strParams) {
		warn(strMsgID, strParams, null);
	}

	public void warn(String strMsgID, Exception e) {
		String[] strParams = null;
		warn(strMsgID, strParams, e);
	}

	public void warn(String strMsgID, String strParam1, Exception e) {
		String[] strParams = new String[1];
		strParams[0] = strParam1;
		warn(strMsgID, strParams, e);
	}

	public void warn(String strMsgID, String strParam1, String strParam2,
			Exception e) {
		String[] strParams = new String[2];
		strParams[0] = strParam1;
		strParams[1] = strParam2;
		warn(strMsgID, strParams, e);
	}

	public void warn(String strMsgID, String[] strParams, Exception e) {
		String strMsg = getForamtedMsg(strMsgID, strParams);
		if (e == null) {
			logger.warn(strMsg);
		} else {
			logger.warn(strMsg, e);
		}
	}

	public void info(String strMsgID) {
		String[] strParams = null;
		info(strMsgID, strParams);
	}

	public void info(String strMsgID, String strParam1) {
		String[] strParams = new String[1];
		strParams[0] = strParam1;
		info(strMsgID, strParams);
	}

	public void info(String strMsgID, String strParam1, String strParam2) {
		String[] strParams = new String[2];
		strParams[0] = strParam1;
		strParams[1] = strParam2;
		info(strMsgID, strParams);
	}

	public void info(String strMsgID, String[] strParams) {
		String strMsg = getForamtedMsg(strMsgID, strParams);
		logger.info(strMsg);
	}

	public void debug(String strMsg) {
		logger.debug(strMsg);
	}

	private String getForamtedMsg(String strMsgID, String[] strParams) {
		StringBuffer sb = new StringBuffer(strMsgID);
		if (strParams != null) {
			for (int i = 0; i < strParams.length; i++) {
				sb.append(strParams[i]);
			}
		}
		return sb.toString();
	}

	public boolean initLogger() {

		try {
			String confpath = Constant.confpath + "xmllog4jconfig.xml";
			File logFile = new File(confpath);
			if (logFile.isFile() && logFile.canRead()) {
				DOMConfigurator.configure(confpath);
			} else {
				throw new LogicException("LogConf Error", confpath);
			}
		} catch (Exception e) {
			return false;
		}
		return true;
	}
}
