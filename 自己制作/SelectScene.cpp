#include "SelectScene.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "PracticeTypingScene_1.h"
#include "PracticeTypingScene_2.h"
#include "WordTypingScene.h"

//============================================================
// コンストラクタ
// 初期状態は「ゲーム選択画面」から開始する
//============================================================
SelectScene::SelectScene()
{
    //最初はゲーム選択画面
    state = SELECT_GAME;
   
    //カーソル初期位置
    cursor = 0;
    maxcursor = 2;

    //画面サイズ取得
    GetDrawScreenSize(&screenW, &screenH);

    //背景画像読み込み
    selectImage = LoadGraph(TEXT("Resource/blackboard.png"));
}

//============================================================
// デストラクタ
//============================================================
SelectScene::~SelectScene()
{
    DeleteGraph(selectImage);
}


//============================================================
// 更新処理
//============================================================
void SelectScene::Update()
{
    nowSpace = CheckHitKey(KEY_INPUT_SPACE);
    nowUp = CheckHitKey(KEY_INPUT_UP);
    nowDown = CheckHitKey(KEY_INPUT_DOWN);

    // ====== ゲーム選択フェーズ ======
    if (state == SELECT_GAME)
    {
        // ↓キーでカーソルを下へ移動
        if (nowDown && !prevDown)
        {
            if (cursor == 0) {
                cursor++;
            }
        }

        // ↑キーでカーソルを上へ移動
        if (nowUp && !prevUp)
        {
            if (cursor == 1) {
                cursor--;
            }
        }

        //------------------------------------------------------------
        // スペースキーで決定
        //------------------------------------------------------------
        if (nowSpace && !prevSpace)
        {
            //選択SE再生
            PlaySoundMem(SoundManager::selectSE, DX_PLAYTYPE_BACK);

            //タイピング練習
            if (cursor == 0)
            {
                state = SELECT_MODE;
                cursor = 0;
            }

            //単語タイピング
            else if (cursor == 1)
            {
                state = SELECT_DIFFICULTY;
                cursor = 0; // 難易度選択の一番上へ
            }
        }
    }
    
    //============================================================
    // モード選択フェーズ
    //============================================================
    else if (state == SELECT_MODE)
    {
        // ↓キー
        if (nowDown && !prevDown)
        {
            if (cursor < 1) {
                cursor++;
            }
        }

        // ↑キー
        if (nowUp && !prevUp)
        {
            if (cursor > 0) {
                cursor--;
            }
        }

        //------------------------------------------------------------
        // モード決定
        //------------------------------------------------------------
        if (nowSpace && !prevSpace)
        {
            //選択SE再生
            PlaySoundMem(SoundManager::selectSE, DX_PLAYTYPE_BACK);

            //一文字タイピング練習
            if (cursor == 0)
            {
                GameManager::GetInstance().ChangeScene(new PracticeTypingScene_1());
            }

            //アルファベットタイピング練習
            else if (cursor == 1)
            {
                GameManager::GetInstance().ChangeScene(new PracticeTypingScene_2());
            }
        }
    }

    //============================================================
    // 難易度選択フェーズ
    //============================================================
    else if (state == SELECT_DIFFICULTY)
    {
        //↓キー
        if (nowDown && !prevDown)
        {
            if (cursor<maxcursor) {
                cursor++;
            }
        }

        // ↑キー
        if (nowUp && !prevUp)
        {
            if (cursor>0) {
                cursor--;
            }
        }

        //------------------------------------------------------------
        // 難易度決定
        //------------------------------------------------------------
        if (nowSpace && !prevSpace)
        {
            //選択SE再生
            PlaySoundMem(SoundManager::selectSE, DX_PLAYTYPE_BACK);

            // かんたん
            if (cursor == 0)
            {
                GameManager::GetInstance().SetDifficulty(EASY);
                GameManager::GetInstance().ChangeScene(new WordTypingScene());
            }
            // ふつう
            else if (cursor == 1)
            {
                GameManager::GetInstance().SetDifficulty(NORMAL);
                GameManager::GetInstance().ChangeScene(new WordTypingScene());
            }
            // むずかしい
            else if (cursor == 2)
            {
                GameManager::GetInstance().SetDifficulty(HARD);
                GameManager::GetInstance().ChangeScene(new WordTypingScene());
            }
        }
    }
    //------------------------------------------------------------
    // 前フレームの入力状態を保存
    //------------------------------------------------------------
    prevSpace = nowSpace;
    prevUp = nowUp;
    prevDown = nowDown;
}

//============================================================
// 描画処理
//============================================================
void SelectScene::Draw()
{
    //背景画像を画面全体に表示
    DrawExtendGraph(0,0,screenW, screenH,selectImage,TRUE);

    ///タイトル表示
    SetFontSize(60);
    DrawString(180, 30, TEXT("ゲーム選択"), GetColor(230, 230, 230));

    //============================================================
    // ゲーム選択表示
    //============================================================
    if (state == SELECT_GAME)
    {
        SetFontSize(30);
        DrawString(220, 190, TEXT("タイピング練習"), GetColor(230, 230, 230));
        DrawString(220, 290, TEXT("単語タイピング"), GetColor(230, 230, 230));

        // カーソル表示
        if (cursor == 0)
        {
            DrawString(190, 190, TEXT("→"), GetColor(230, 230, 230));
        }
        else if (cursor == 1)
        {
            DrawString(190, 290, TEXT("→"), GetColor(230, 230, 230));
        }
    }

    SetFontSize(27);
    //------------------------------------------------------------
    // モード選択表示
    //------------------------------------------------------------
    if (state == SELECT_MODE)
    {
        DrawString(100, 190, TEXT(" 1文字タイピング練習"), GetColor(230, 230, 230));
        DrawString(100, 280, TEXT(" アルファベットタイピング練習"), GetColor(230, 230, 230));

        if (cursor == 0)
        {
            DrawString(80, 190, TEXT("→"), GetColor(230, 230, 230));
        }
        else if (cursor == 1)
        {
            DrawString(80, 280, TEXT("→"), GetColor(230, 230, 230));
        }
    }
    
    SetFontSize(50);
    //------------------------------------------------------------
    // 難易度選択表示
    //------------------------------------------------------------
    if (state==SELECT_DIFFICULTY)
    {
        DrawString(180, 150, TEXT(" かんたん"), GetColor(100, 200, 255));
        DrawString(180, 250, TEXT(" ふつう"), GetColor(255, 255, 100));
        DrawString(180, 350, TEXT(" むずかしい"), GetColor(255, 100, 100));

        if (cursor == 0)
        {
            DrawString(160, 150, TEXT("→"), GetColor(230, 230, 230));
        }
        else if (cursor == 1)
        {
            DrawString(160, 250, TEXT("→"), GetColor(230, 230, 230));
        }
        else if (cursor == 2)
        {
            DrawString(160, 350, TEXT("→"), GetColor(230, 230, 230));
        }
    }

    //------------------------------------------------------------
    // 選択案内
    //------------------------------------------------------------
    SetFontSize(18);
    DrawString(500, 400, TEXT("Spaceで選択"), GetColor(230, 230, 230));
}
