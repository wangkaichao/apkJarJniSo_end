package com.coocaa.factory.function;

import java.io.File;

import android.content.Context;

import com.tianci.plugins.factory.BaseFactoryManager;

import dalvik.system.DexClassLoader;

public class LoadPlugin
{
    private final static String pluginFilePath = "/system/plugins/AtomicFactoryPlugin.jar";
    private final static String pluginClazz = "com.skyworth.factory.FactoryManager";
    private static BaseFactoryManager mFactoryManager = null;

    public static BaseFactoryManager LoadFactoryManager(Context context)
    {
        if (new File(pluginFilePath).exists())
        {
            DexClassLoader loader = new DexClassLoader(pluginFilePath,
                    context.getDir("dex", 0).getAbsolutePath(), null, context.getClassLoader());
            try
            {
                mFactoryManager = (BaseFactoryManager) loader.loadClass(pluginClazz).newInstance();
            } catch (InstantiationException e)
            {
                e.printStackTrace();
            } catch (IllegalAccessException e)
            {
                e.printStackTrace();
            } catch (ClassNotFoundException e)
            {
                e.printStackTrace();
            }
        }
        return mFactoryManager;
    }
}