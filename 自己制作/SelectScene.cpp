#include "SelectScene.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "PracticeTypingScene_1.h"
#include "PracticeTypingScene_2.h"
#include "WordTypingScene.h"

//============================================================
// 描画用定数
//============================================================

const int TITLE_X = 180;   // タイトルのX座標
const int TITLE_Y = 30;    // タイトルのY座標

const int GAME_TEXT_X = 220;      // ゲーム選択のX座標
const int GAME_CURSOR_X = 190;    // ゲーム選択カーソルのX座標
const int GAME_Y1 = 190;          // 1つ目のゲームY座標  
const int GAME_Y2 = 290;          // 2つ目のゲームY座標

const int MODE_TEXT_X = 100;      // モード選択のX座標
const int MODE_CURSOR_X = 80;     // モード選択カーソルのX座標
const int MODE_Y1 = 190;          // 1つ目のモードY座標
const int MODE_Y2 = 280;          // 2つ目のモードY座標

const int DIFFICULTY_TEXT_X = 180;     // 難易度選択のX座標
const int DIFFICULTY_CURSOR_X = 150;   // 難易度選択カーソルのX座標
const int DIFFICULTY_Y1 = 150;         // 難易度(かんたん)のY座標
const int DIFFICULTY_Y2 = 250;         // 難易度(ふつう)のY座標
const int DIFFICULTY_Y3 = 350;         // 難易度(むずかしい)のY座標

const int SELECT_TEXT_X = 500;    // 選択テキストのX座標
const int SELECT_TEXT_Y = 400;    // 選択テキストのY座標

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
    DrawString(TITLE_X, TITLE_Y, TEXT("ゲーム選択"), GetColor(230, 230, 230));

    //============================================================
    // ゲーム選択表示
    //============================================================
    if (state == SELECT_GAME)
    {
        SetFontSize(30);
        DrawString(GAME_TEXT_X, GAME_Y1, TEXT("タイピング練習"), GetColor(230, 230, 230));
        DrawString(GAME_TEXT_X, GAME_Y2, TEXT("単語タイピング"), GetColor(230, 230, 230));

        int y = (cursor == 0) ? GAME_Y1 : GAME_Y2;
        DrawString(GAME_CURSOR_X, y, TEXT("→"), GetColor(230, 230, 230));
    }

    SetFontSize(27);
    //------------------------------------------------------------
    // モード選択表示
    //------------------------------------------------------------
    if (state == SELECT_MODE)
    {
        DrawString(MODE_TEXT_X, MODE_Y1, TEXT(" 1文字タイピング練習"), GetColor(230, 230, 230));
        DrawString(MODE_TEXT_X, MODE_Y2, TEXT(" アルファベットタイピング練習"), GetColor(230, 230, 230));

        int y = (cursor == 0) ? MODE_Y1 : MODE_Y2;
        DrawString(MODE_CURSOR_X, y, TEXT("→"), GetColor(230, 230, 230));
    }
    
    SetFontSize(50);
    //------------------------------------------------------------
    // 難易度選択表示
    //------------------------------------------------------------
    if (state==SELECT_DIFFICULTY)
    {
        DrawString(DIFFICULTY_TEXT_X, DIFFICULTY_Y1, TEXT(" かんたん"), GetColor(100, 200, 255));
        DrawString(DIFFICULTY_TEXT_X, DIFFICULTY_Y2, TEXT(" ふつう"), GetColor(255, 255, 100));
        DrawString(DIFFICULTY_TEXT_X, DIFFICULTY_Y3, TEXT(" むずかしい"), GetColor(255, 100, 100));

        int y;

        switch (cursor)
        {
        case 0:
            y = DIFFICULTY_Y1;
            break;
        case 1:
            y = DIFFICULTY_Y2;
            break;
        case 2:
            y = DIFFICULTY_Y3;
            break;
        }
        
        DrawString(DIFFICULTY_CURSOR_X, y, TEXT("→"), GetColor(230, 230, 230));
    }

    //------------------------------------------------------------
    // 選択案内
    //------------------------------------------------------------
    SetFontSize(18);
    DrawString(SELECT_TEXT_X, SELECT_TEXT_Y, TEXT("Spaceで選択"), GetColor(230, 230, 230));
}
