package com.searchlocal.util;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

import com.searchlocal.exception.LogicException;

/**
 * 加密程序
 */
public class Encrypt {

	private static CLogger logger = new CLogger(Encrypt.class);

	private final static String DIGEST_NAME = "MD5";

	private final static String EXTENCRYPTSTR = "cs";

	/**
	 * MessageDigest md = MessageDigest.getInstance("SHA-1"); byte[]
	 * digestedBytes = md.digest(password.getBytes()); return new
	 * String(digestedBytes);
	 */
	public static String digest(String unEncrypt) throws LogicException {
		MessageDigest md5;
		unEncrypt = EXTENCRYPTSTR + unEncrypt;
		String encodeStr = null;
		try {
			md5 = MessageDigest.getInstance(DIGEST_NAME);
		} catch (NoSuchAlgorithmException e1) {
			e1.printStackTrace();
			throw new LogicException("取得加密实例失败：" + e1.getMessage());
		}

		// byte[] gb = unEncrypt.getBytes();
		// log.debug("len:"+gb.length);
		md5.update(unEncrypt.getBytes());
		byte[] e = md5.digest();
		logger.debug("E len:" + e.length);
		// for (int i = 0;i < e.length;i++)
		// log.debug(" E byte i:"+i+e[i]);

		encodeStr = byteToHexString(e);

		return encodeStr;

	}

	private static String byteToHexString(byte b[]) {
		String hs = "";
		String stmp = "";
		for (int n = 0; n < b.length; n++) {
			stmp = (java.lang.Integer.toHexString(b[n] & 0XFFFF));
			stmp = "0000" + stmp;
			stmp = stmp.substring(stmp.length() - 4);
			hs = hs + stmp;
		}
		return hs.toUpperCase();
	}

	private static boolean isEnqual(String a, String b) throws LogicException {
		String astring = digest(a);
		return astring.equals(b);
	}

	
}