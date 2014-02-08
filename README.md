non-recursive make with googletest for TDD
======================

## 概要

非再帰的makeを用いてソースツリーを管理し、テストコードを含むソースツリーのテストコードかテスト対象コードいずれか更新すると、**関係するコードのみがコンパイルされてテストが走る**ように、複雑な分割コンパイルとテストの実行を支援します。

### 目的

このMakefileは、分割コンパイルの自動化はもちろんですが、googletestを用いて中規模以上のコードに対してTDDを実践するためにもあります。

コードの規模がある程度大きくなり、コード間の依存関係が複雑になっても、`make`や`make test`を叩いた時に走るビルドを変更箇所のみに極小化することで、フィードバックサイクルをなるべく早く回すことが目的です。

**RED -> GREEN -> refactoring**

## とりあえずサンプルのビルドを試してみる

```sh
git clone https://github.com/doi-t/nonrec-make-with-gtest.git
cd nonrec-make-with-gtest/
make setup_gtest
make test
make
```

## 使い方

ソースツリーは、Makefileの仕様に従って、厳密に管理する必要があるため、以下の手順でサブディレクトリおよびソースファイルの追加を行います。

1. mkRulesスクリプトで必要なサブディレクトリを生成します。bin, lib, test以下には複数のサブディレクトを生成できます。

2. ソースツリーのサブディレクトリを管理するRules.mkに必要な設定(後述)を行います。依存ライブラリやテスト対象ライブラリの指定にはlib/から始まるパスを指定するように注意して下さい。

3. ソースを.ccファイルとして、ヘッダを.hファイルとして作成します。各サブディレクトリ内部に、複数の.ccファイルがあっても構いません。これらはビルド時にサブディレクトリ単位で１つのライブラリや実行バイナリにまとめられます。

4. テストのビルドおよび実行を行いたい場合は、`make test`を実行して下さい。実行バイナリのビルドを行いたい場合は、`make`を実行して下さい。

コード間の依存関係はmakeで管理しているので、以降ソースファイルを変更して`make`や`make test`を実行すると、変更したコードに関わるコンパイルのみ実行されます。

## コマンドの概要

リポジトリには、足し算を行うモジュール、それに対するテスト、実装したモジュールを呼び出すメインルーチンのサンプルを含んでいます。

git cloneしてきた直後に`make`や`make test`を叩けば、サンプルコードのビルドとテストの実行を確認することができます。

googletestをセットアップしてない場合は、先に`make setup_gtest`を実行して下さい。

### make

トップレベルMakefileがあるディレクトリで`make`を叩くと実行バイナリが依存するライブラリのコンパイルと実行バイナリ自身のビルドが始まります。

	make

### make test

トップレベルMakefileがあるディレクトリで、`make test`を叩くとテストが対象としているライブラリのビルドとテスト自身のビルドが始まります。

テスト用バイナリは、ビルドが完了する度に実行されます。

	make test

### make clean

依存関係ファイルや、生成された実行バイナリやライブラリを全て削除します。

	make clean

### make debug

トップレベルMakefileが集約した情報を表示する

	make debug

### googletest install

googletestは/usr/local以下にライブラリを配置する形で利用しています。

Makefileにセットアップ用のシェルスクリプトを呼び出すコマンドがあるのでこれを実行して下さい。

	make setup_gtest

### googletest uninstall

不要になったら以下で/usr/local以下に配置したヘッダファイルとライブラリを削除できます。

	make remove_gtest

### mkRules

ソースツリーにサブディレクトリを追加する際に実行します。詳細は後述。

例:

	./mkRules -b foo

	./mkRules -l bar

	./mkRules -t hoge

## ソースツリーの管理

git cloneしてきた直後はセットアップ用のスクリプト群とサンプルコードが入っています。

サンプルコードが不要なら、ソースツリーの最小構成をセットアップ用のシェルスクリプトで再構築して下さい。

	./setup

bin, lib, testの３つのディレクトリを全て削除して、再度生成します。

生成されるディレクトリはそれぞれ、実行バイナリ(bin), ライブラリ(lib), テスト(test)に対応します。

### サブディレクトリを管理するMakefileの断片(Rules.mk)を生成する

mkRulesはサブディレクトリの管理するRules.mkの雛形を生成するスクリプトです。

Rules.mkを生成する際は、目的に応じて必須オプション(-b:実行バイナリ(bin), -l:ライブラリ(lib), -t:テスト(test))を指定します。

必須オプションに続いてサブディレクトリの名前を指定します。サブディレクトリ名の指定も必須です。

例えば、新たにsampleという名前のディレクトリに実行バイナリを追加する場合は、

	./mkRules.mk -b sample

実行するとソースツリーが以下のようになります。Rules.mkと一緒にサブディレクトリと同名のテンプレート(sample.cc, sample.h)も生成します(必ずこのテンプレートを使わなければならないわけではありません)。

```
nonrec-make-with-gtest/
|-- Makefile
`-- bin
    `-- sample
        |-- Rules.mk
        |-- sample.cc
        `-- sample.h
```

ライブラリとテストについても同様です。

addというサブディレクトリ名のライブラリとテストを追加する例を以下に示します。

ライブラリの場合

	./mkRules.mk -l add

実行結果

```
nonrec-make-with-gtest/
|-- Makefile
`-- lib
	`-- add
	    |-- Rules.mk
	    |-- add.cc
	    `-- add.h
```

テストの場合

	./mkRules.mk -t add

実行結果

```
nonrec-make-with-gtest/
|-- Makefile
`-- test
	`-- add
	    |-- Rules.mk
	    `-- test_add.cc
```

### ソースツリー構成

非再帰的makeでは、ソースツリーを構成するサブディレクトリに配置されたMakefileの断片(Rules.mk)を、

トップレベルのMakefileがincludeすることでサブディレクトリの情報を集約してからソースツリー全体のコンパイルを行います。

各サブディレクトリでローカルな設定はRules.mkで管理します(指定した名前に応じて、デフォルトの値が設定されています)。

```
nonrec-make-with-gtest/
|-- Makefile   <--- トップレベルMakefile
|-- bin
|   `-- sample   <--- binディレクトリ以下の各サブディレクトリが1つの実行バイナリに対応
|       |-- Rules.mk   <--- デフォルトではsampleという実行バイナリが生成されるように設定されています。
|       |-- sample.cc
|       `-- sample.h
|-- lib
|   `-- add   <--- libディレクトリ以下の各サブディレクトリが1つのライブラリに対応
|       |-- Rules.mk   <--- デフォルトでlibadd.aというライブラリが生成されるように設定されます。
|       |-- add.cc
|       `-- add.h
`-- test
    `-- add   <--- testディレクトリ以下の各サブディレクトリが1つのテスト用バイナリに対応
        |-- Rules.mk    <--- デフォルトでtest_addというテスト用バイナリが生成されるように設定されています。
        `-- test_add.cc
```

#### 生成されたlib/add/Rules.mkの管理

Rules.mkにはデフォルトでライブラリ名としてlibadd.aという名前が設定されています。必要に応じて変更して下さい。

必要な機能を.ccファイルとして複数追加できます。それらをコンパイルして生成されたオブジェクトファイルは全て１つのライブラリにまとめられます。

```make
library-name := libadd.a
local_src := $(wildcard $(subdirectory)/*.cc)

$(eval $(call make-library, $(subdirectory)/$(library-name), $(local_src)))
```

#### 生成されたtest/add/Rules.mkの管理

Rules.mkにはデフォルトで生成されるテスト用バイナリの名前が設定されています。

変数target_librariesに**テスト対象のモジュールを含むライブラリ名を全て指定**して下さい。

必要なテストスイートを.ccファイルとして複数追加できます。それらをコンパイルして生成されたオブジェクトファイルは全て１つのテスト用バイナリにまとめられます。

```make
local_test_suites := test_add
target_libraries := lib/add/libadd.a
local_src := $(wildcard $(subdirectory)/*.cc)

$(eval $(call make-test, $(subdirectory)/$(local_test_suites), $(local_src), $(target_libraries)))
```

#### 生成されたbin/sample/Rules.mkの管理

Rules.mkにはデフォルトで生成される実行バイナリの名前が設定されています。

変数dependent-librariesに実行バイナリが**依存するライブラリ名を全て指定**して下さい。

```make
exec-binary-name := sample
dependent-libraries := lib/add/libadd.a
local_src := $(wildcard $(subdirectory)/*.cc)

$(eval $(call make-exec-binary, $(subdirectory)/$(exec-binary-name), $(local_src), $(dependent-libraries)))
