[SCE CONFIDENTIAL DOCUMENT]
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
                     Copyright (C) 2007 Sony Computer Entertainment Inc.
                                                     All Rights Reserved

サンプルフレームワークの使用方法を示すサンプルプログラム

<サンプルの解説>
    このサンプルは、初期化、入力処理、テキストレンダリングなどのために
    サンプルフレームワークを使用するサンプルプログラムです。

    テストする主な関数は、アプリケーションのコールバック関数である
    TestApp::onInit()、TestApp::onRender()、TestApp::onSize()、および
    TestApp::onShutdown()です。

    TestApp::onInit()は、起動時に呼ばれ、アプリケーションが必要とする
    任意のリソースの確保を行います。TestApp::onRender()は、
    フレーム毎に呼ばれ、シーンのレンダリングに使用されます。
    TestApp::onSize()は、実行中に表示解像度が変更されると呼ばれます。
    TestApp::onShutdown()は、アプリケーションの終了時に呼ばれ、
    アプリケーションが確保していた任意のリソースの解放を可能にします。

<ファイル>
    TestApp.cpp, TestApp.h

<起動方法>
        $ make          ：コンパイル


<コントローラの操作方法>
    コントローラをUSBポートに接続して、カメラを動かすことがが可能です。
    左スティックを用いてカメラを回転させ、右スティックを用いてカメラを移動させ
    ます。

<HID入力のステータスの表示>
    コントローラ、キーボード、およびマウスの入力は、画面上で監視が
    可能です。キーボードの入力に関しては、スペースキーのみが検出されます。

<注意>
    なし

