# Add project specific ProGuard rules here.
-keepclasseswithmembernames class * {
    native <methods>;
}
-keepclassmembers class * {
    public <init>(...);
}
-keep class com.selaura.client.** { *; }
