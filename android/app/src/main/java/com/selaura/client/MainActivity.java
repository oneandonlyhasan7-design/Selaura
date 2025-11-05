package com.selaura.client;

import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;
import java.util.Arrays;
import java.util.List;

public class MainActivity extends Activity {
    
    static {
        System.loadLibrary("selaura_runtime");
    }

    private static final List<String> MINECRAFT_PACKAGES = Arrays.asList(
        "com.mojang.minecraftpe",
        "com.mojang.minecraftpe.demo",
        "com.mojang.minecraftpe.trial",
        "com.mojang.minecraftpe.beta",
        "com.mojang.minecraftpe.preview"
    );

    private String detectedMinecraftPackage = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView statusText = findViewById(R.id.statusText);
        TextView versionText = findViewById(R.id.versionText);
        Button launchButton = findViewById(R.id.launchButton);

        versionText.setText(getString(R.string.version_info));
        
        detectedMinecraftPackage = detectMinecraft();
        
        if (detectedMinecraftPackage != null) {
            statusText.setText("Minecraft detected: " + getMinecraftVersion(detectedMinecraftPackage));
            launchButton.setEnabled(true);
            launchButton.setOnClickListener(v -> launchMinecraft());
        } else {
            statusText.setText(getString(R.string.minecraft_not_found));
            launchButton.setEnabled(false);
        }
        
        initNative();
    }

    private String detectMinecraft() {
        PackageManager pm = getPackageManager();
        for (String packageName : MINECRAFT_PACKAGES) {
            try {
                PackageInfo info = pm.getPackageInfo(packageName, 0);
                if (info != null) {
                    return packageName;
                }
            } catch (PackageManager.NameNotFoundException e) {
            }
        }
        return null;
    }

    private String getMinecraftVersion(String packageName) {
        try {
            PackageInfo info = getPackageManager().getPackageInfo(packageName, 0);
            return info.versionName;
        } catch (PackageManager.NameNotFoundException e) {
            return "Unknown";
        }
    }

    private void launchMinecraft() {
        if (detectedMinecraftPackage == null) {
            Toast.makeText(this, getString(R.string.minecraft_not_found), Toast.LENGTH_SHORT).show();
            return;
        }

        try {
            Intent launchIntent = getPackageManager().getLaunchIntentForPackage(detectedMinecraftPackage);
            if (launchIntent != null) {
                Toast.makeText(this, "Launching Minecraft with Selaura Client...", Toast.LENGTH_SHORT).show();
                startActivity(launchIntent);
                finish();
            }
        } catch (Exception e) {
            Toast.makeText(this, "Failed to launch: " + e.getMessage(), Toast.LENGTH_LONG).show();
        }
    }

    private native void initNative();
}
