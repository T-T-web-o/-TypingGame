#include "SelectScene.h"
#include "GameManager.h"
#include "PracticeTypingScene_1.h"
#include "PracticeTypingScene_2.h"
#include "WordTypingScene.h"

// 初期状態は「ゲーム選択画面」から開始する
SelectScene::SelectScene()
{
    state = SELECT_GAME;
   
    cursor = 0;
    maxcursor = 2;

    //画面サイズ取得
    GetDrawScreenSize(&screenW, &screenH);

    //背景画像読み込み
    selectImage = LoadGraph(TEXT("Resource/blackboard.png"));
}

SelectScene::~SelectScene()
{
    DeleteGraph(selectImage);
}


// セレクトシーンの更新処理
void SelectScene::Update()
{
    nowSpace = CheckHitKey(KEY_INPUT_SPACE);
    nowUp = CheckHitKey(KEY_INPUT_UP);
    nowDown = CheckHitKey(KEY_INPUT_DOWN);

    // ====== ゲーム選択フェーズ ======
    if (state == SELECT_GAME)
    {
        //↓キーで下へ
        if (nowDown && !prevDown)
        {
            if (cursor == 0) {
                cursor++;
            }
        }

        // ↑キーで上へ
        if (nowUp && !prevUp)
        {
            if (cursor == 1) {
                cursor--;
            }
        }

        //スペースキーで選択
        if (nowSpace && !prevSpace)
        {
            if (cursor == 0)
            {
                state = SELECT_MODE;
                cursor = 0;
            }
            else if (cursor == 1)
            {
                state = SELECT_DIFFICULTY;
                cursor = 0; // 難易度選択の一番上へ
            }
        }
    }
    
    //====== モード選択フェーズ ======
    else if (state == SELECT_MODE)
    {
        //↓キーで下へ
        if (nowDown && !prevDown)
        {
            if (cursor < 1) {
                cursor++;
            }
        }

        // ↑キーで上へ
        if (nowUp && !prevUp)
        {
            if (cursor > 0) {
                cursor--;
            }
        }

        if (nowSpace && !prevSpace)
        {
            if (cursor == 0)
            {
                GameManager::GetInstance().ChangeScene(new PracticeTypingScene_1());
            }
            else if (cursor == 1)
            {
                GameManager::GetInstance().ChangeScene(new PracticeTypingScene_2());
            }
        }
    }

    // ====== 難易度選択フェーズ ======
    else if (state == SELECT_DIFFICULTY)
    {
        //↓キーで下へ
        if (nowDown && !prevDown)
        {
            if (cursor<maxcursor) {
                cursor++;
            }
        }

        // ↑キーで上へ
        if (nowUp && !prevUp)
        {
            if (cursor>0) {
                cursor--;
            }
        }

        //スペースキーで選択
        if (nowSpace && !prevSpace)
        {
            //0:EASY
            if (cursor == 0)
            {
                GameManager::GetInstance().SetDifficulty(EASY);
                GameManager::GetInstance().ChangeScene(new WordTypingScene());
            }
            //1:NORMAL
            else if (cursor == 1)
            {
                GameManager::GetInstance().SetDifficulty(NORMAL);
                GameManager::GetInstance().ChangeScene(new WordTypingScene());
            }
            //2:HARD
            else if (cursor == 2)
            {
                GameManager::GetInstance().SetDifficulty(HARD);
                GameManager::GetInstance().ChangeScene(new WordTypingScene());
            }
        }
    }
    prevSpace = nowSpace;
    prevUp = nowUp;
    prevDown = nowDown;
}

// セレクトシーンの描画処理
void SelectScene::Draw()
{
    //背景画像を画面全体に表示
    DrawExtendGraph(0,0,screenW, screenH,selectImage,TRUE);

    ///タイトル表示
    SetFontSize(50);
    DrawString(200, 30, TEXT("ゲーム選択"), GetColor(230, 230, 230));

    //====== ゲーム選択表示 ======
    if (state == SELECT_GAME)
    {
        SetFontSize(30);
        DrawString(220, 190, TEXT("タイピング練習"), GetColor(230, 230, 230));
        DrawString(220, 290, TEXT("単語タイピング"), GetColor(230, 230, 230));
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
    //====== モード選択表示 ======
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

    //====== 難易度選択表示 ======
    if (state==SELECT_DIFFICULTY)
    {
        DrawString(200, 200, TEXT(" かんたん"), GetColor(230, 230, 230));
        DrawString(200, 250, TEXT(" ふつう"), GetColor(230, 230, 230));
        DrawString(200, 300, TEXT(" むずかしい"), GetColor(230, 230, 230));

        if (cursor == 0)
        {
            DrawString(180, 200, TEXT("→"), GetColor(230, 230, 230));
        }
        else if (cursor == 1)
        {
            DrawString(180, 250, TEXT("→"), GetColor(230, 230, 230));
        }
        else if (cursor == 2)
        {
            DrawString(180, 300, TEXT("→"), GetColor(230, 230, 230));
        }
    }

    SetFontSize(18);
    DrawString(500, 400, TEXT("Spaceで選択"), GetColor(230, 230, 230));
}
