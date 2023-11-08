#include "../SDL/lib/sim.h"
#include <SDL2/SDL.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

static const int WORLD_SIZE = 50;

static SDL_Renderer *renderer = NULL;

SDL_Renderer* createRenderer()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) { exit(EXIT_FAILURE); }
    SDL_Window *win = SDL_CreateWindow("Game Of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WORLD_SIZE, WORLD_SIZE, SDL_WINDOW_SHOWN);
    if (win == NULL) { exit(EXIT_FAILURE);}
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (rend == NULL) { exit(EXIT_FAILURE); }
    return rend;
}

void drawWorld(bool world[WORLD_SIZE][WORLD_SIZE])
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int y = 0; y < WORLD_SIZE; ++y)
    {
        for (int x = 0; x < WORLD_SIZE; ++x)
        {
            if (!world[y][x]) continue;
            SDL_Rect point = {x, y, 1, 1};
            SDL_RenderFillRect(renderer, &point);
        }
    }

    SDL_RenderPresent(renderer);
}

void stopDrawing()
{
    SDL_Quit();
}




#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

int main() {
  LLVMContext context;
  // ; ModuleID = 'app'
  // source_filename = "app"
  Module *module = new Module("app", context);
  IRBuilder<> builder(context);

  /*
    Define struct and global (static) variable  
  */

  Align align16 = Align(16);
  Align align8  = Align(8);
  Align align4  = Align(4);
  Align align1  = Align(1);

  swapCellsGV->setUnnamedAddr(GlobalValue::UnnamedAddr::Global);
  swapCellsGV->setLinkage(GlobalValue::LinkageTypes::InternalLinkage);
  swapCellsGV->setAlignment(align16);
  swapCellsGV->setInitializer(ConstantAggregateZero::get(arrayType));


  /*
    Declare external functions
  */

  // // declare i32 @rand() local_unnamed_addr #1
  // FunctionType *simRandFuncType = FunctionType::get(builder.getInt32Ty(), false);
  // FunctionCallee simRandFunc = module->getOrInsertFunction("simRand", simRandFuncType);

  // declare void @drawWorld(i8* noundef) local_unnamed_addr #5
  FunctionType *drawWorldFuncType = FunctionType::get(builder.getVoidTy(), {builder.getInt8PtrTy()}, false);
  FunctionCallee drawWorldFunc = module->getOrInsertFunction("drawWorld", drawWorldFuncType);

  /*
    Define main functions
  */

  // define dso_local void @generateWorld(i8* nocapture noundef writeonly %0) local_unnamed_addr #0
  FunctionType *generateWorldFuncType = FunctionType::get(builder.getVoidTy(), {builder.getInt8PtrTy()}, false);
  Function *generateWorldFunc = Function::Create(generateWorldFuncType, Function::ExternalLinkage, "generateWorld", module);
  generateWorldFunc->setDSOLocal(true);
  generateWorldFunc->setUnnamedAddr(GlobalValue::UnnamedAddr::Local);

  // define dso_local i32 @toUint(i8* nocapture noundef readonly %0, i32 noundef %1, i32 noundef %2) local_unnamed_addr #2
  FunctionType *toUintFuncType = FunctionType::get(builder.getInt32Ty(), {builder.getInt8PtrTy(), builder.getInt32Ty(), builder.getInt32Ty()}, false);
  Function *toUintFunc = Function::Create(toUintFuncType, Function::ExternalLinkage, "toUint", module);
  toUintFunc->setDSOLocal(true);
  toUintFunc->setUnnamedAddr(GlobalValue::UnnamedAddr::Local);

  // define dso_local void @updateCell(i1 noundef zeroext %0, i8* nocapture noundef writeonly %1, i32 noundef %2) local_unnamed_addr #3
  FunctionType *updateWorldFuncType = FunctionType::get(builder.getVoidTy(), {builder.getInt1Ty(), builder.getInt8PtrTy(), builder.getInt32Ty()}, false);
  Function *updateWorldFunc = Function::Create(updateWorldFuncType, Function::ExternalLinkage, "updateCell", module);
  updateWorldFunc->setDSOLocal(true);
  updateWorldFunc->setUnnamedAddr(GlobalValue::UnnamedAddr::Local);

  // define dso_local void @updateWorld(i8* nocapture noundef readonly %0, i8* nocapture noundef writeonly %1) local_unnamed_addr #4
  FunctionType *updateWorldFuncType = FunctionType::get(builder.getVoidTy(), {builder.getInt8PtrTy(), builder.getInt8PtrTy()}, false);
  Function *updateWorldFunc = Function::Create(updateWorldFuncType, Function::ExternalLinkage, "updateWorld", module);
  updateWorldFunc->setDSOLocal(true);
  updateWorldFunc->setUnnamedAddr(GlobalValue::UnnamedAddr::Local);

  // define dso_local void @app() local_unnamed_addr #0
  FunctionType *appFuncType = FunctionType::get(builder.getVoidTy(), false);
  Function *appFunc = Function::Create(appFuncType, Function::ExternalLinkage, "app", module);
  appFunc->setDSOLocal(true);
  appFunc->setUnnamedAddr(GlobalValue::UnnamedAddr::Local);

  /*
    Actual IR for generateWorld() function
  */
  {
    // Declare all basic blocks in advance
    BasicBlock *bBlock0   = BasicBlock::Create(context, "", generateWorldFunc);
    BasicBlock *bBlock2   = BasicBlock::Create(context, "", generateWorldFunc);
    BasicBlock *bBlock6   = BasicBlock::Create(context, "", generateWorldFunc);
    BasicBlock *bBlock7   = BasicBlock::Create(context, "", generateWorldFunc);
    BasicBlock *bBlock10  = BasicBlock::Create(context, "", generateWorldFunc);

    Value *value0 = generateWorldFunc->getArg(0);

    // 0:
    builder.SetInsertPoint(bBlock0);

    // br label %2
    builder.CreateBr(bBlock2);

    // 2:
    builder.SetInsertPoint(bBlock3);

    // %3 = phi i64 [ 0, %1 ], [ %8, %7 ]
    PHINode *value3 = builder.CreatePHI(builder.getInt64Ty(), 2);

    // %4 = mul nuw nsw i64 %3, 50
    Value *value4 = builder.CreateMul(value3, builder.getInt64(50), "", true, true);

    // %5 = getelementptr inbounds i8, i8* %0, i64 %4
    Value *value5 = builder.CreateInBoundsGEP(value0, {value4});

    // br label %10
    builder.CreateBr(bBlock10);

    // 6:
    builder.SetInsertPoint(bBlock6);

    // ret void
    builder.CreateRetVoid();

    // 7:
    builder.SetInsertPoint(bBlock7);

    // %8 = add nuw nsw i64 %3, 1
    Value *value8 = builder.CreateAdd(value3, builder.getInt64(1), "", true, true);

    // %9 = icmp eq i64 %8, 50
    Value *value9 = builder.CreateICmpEQ(value8, builder.getInt64(50));

    // br i1 %9, label %6, label %2, !llvm.loop !5
    builder.CreateCondBr(value9, bBlock6, bBlock2);

    /*
      Now resolve all PHI nodes
    */

    value3->addIncoming(builder.getInt64(0), bBlock1);
    value3->addIncoming(value8, bBlock7);
  }

  /*
    Actual IR for toUint() function
  */
  {
    // Declare all basic blocks in advance
    BasicBlock *bBlock0   = BasicBlock::Create(context, "", toUintFunc);
    BasicBlock *bBlock7   = BasicBlock::Create(context, "", toUintFunc);
    BasicBlock *bBlock15  = BasicBlock::Create(context, "", toUintFunc);

    Value *value0 = toUintFunc->getArg(0);
    Value *value1 = toUintFunc->getArg(1);
    Value *value2 = toUintFunc->getArg(2);

    // 0:
    builder.SetInsertPoint(bBlock0);

    // %4 = icmp ugt i32 %2, 49
    Value *value4 = builder.CreateICmpUGT(value2, builder.getInt64(49));

    // %5 = icmp ugt i32 %1, 49
    Value *value5 = builder.CreateICmpUGT(value1, builder.getInt64(49));

    // %6 = or i1 %5, %4
    Value *value160 = builder.CreateOr(value5, value4);

    // br i1 %6, label %15, label %7
    builder.CreateCondBr(value6, bBlock15, bBlock7);

    // 7:
    builder.SetInsertPoint(bBlock7);

    // %8 = zext i32 %1 to i64
    Value *value8 = builder.CreateZExt(value1, builder.getInt64Ty());

    // %9 = mul nuw nsw i64 %8, 50
    Value *value9 = builder.CreateMul(value8, builder.getInt64(50), "", true, true);

    // %10 = getelementptr inbounds i8, i8* %0, i64 %9
    Value *value10 = builder.CreateInBoundsGEP(value0, {value9});

    // %11 = zext i32 %2 to i64
    Value *value11 = builder.CreateZExt(value2, builder.getInt64Ty());

    // %12 = getelementptr inbounds i8, i8* %10, i64 %11
    Value *value5 = builder.CreateInBoundsGEP(value10, {value11});

    // %13 = load i8, i8* %12, align 1, !tbaa !7, !range !12
    Value *value13 = builder.CreateAlignedLoad(value12, align1);

    // %14 = zext i8 %13 to i32
    Value *value14 = builder.CreateZExt(value13, builder.getInt32Ty());

    // br label %15
    builder.CreateBr(bBlock15);

    // 15:
    builder.SetInsertPoint(bBlock15);

    // %16 = phi i32 [ %14, %7 ], [ 0, %3 ]
    PHINode *value16 = builder.CreatePHI(builder.getInt32Ty(), 2);

    // ret i32 %16
    builder.CreateRet(value16);

    /*
      Now resolve all PHI nodes
    */

    value16->addIncoming(value14, bBlock7);
    value16->addIncoming(builder.getInt64(0), bBlock3);
  }

  /*
    Actual IR for updateCell() function
  */
  {
    // Declare all basic blocks in advance
    BasicBlock *bBlock0   = BasicBlock::Create(context, "", updateCellFunc);

    Value *value0 = updateCellFunc->getArg(0);
    Value *value1 = updateCellFunc->getArg(1);
    Value *value2 = updateCellFunc->getArg(2);

    // 0:
    builder.SetInsertPoint(bBlock0);

    // %4 = and i32 %2, -2
    Value *value160 = builder.CreateFAdd(value2, builder.getInt32(-2));

    // %5 = icmp eq i32 %4, 2
    Value *value5 = builder.CreateICmpEQ(value4, builder.getInt32(2));

    // %6 = icmp sgt i32 %2, 2
    Value *value6 = builder.CreateICmpSGT(value2, builder.getInt32(2));

    // %7 = select i1 %0, i1 %5, i1 %6
    Value *value7 = builder.CreateSelect(value0, value5, value6);

    // %8 = zext i1 %7 to i8
    Value *value8 = builder.CreateZExt(value7, builder.getInt8Ty());

    // store i8 %8, i8* %1, align 1, !tbaa !7
    builder.CreateAlignedStore(value8, value1, align1);

    // ret void
    builder.CreateRetVoid();
  }

  /*
    Actual IR for updateWorld() function
  */
  {
    // Declare all basic blocks in advance
    BasicBlock *bBlock0   = BasicBlock::Create(context, "", updateWorldFunc);
    BasicBlock *bBlock3   = BasicBlock::Create(context, "", updateWorldFunc);
    BasicBlock *bBlock18  = BasicBlock::Create(context, "", updateWorldFunc);
    BasicBlock *bBlock19  = BasicBlock::Create(context, "", updateWorldFunc);
    BasicBlock *bBlock21  = BasicBlock::Create(context, "", updateWorldFunc);
    BasicBlock *bBlock27  = BasicBlock::Create(context, "", updateWorldFunc);
    BasicBlock *bBlock33  = BasicBlock::Create(context, "", updateWorldFunc);
    BasicBlock *bBlock35  = BasicBlock::Create(context, "", updateWorldFunc);
    BasicBlock *bBlock40  = BasicBlock::Create(context, "", updateWorldFunc);
    BasicBlock *bBlock45  = BasicBlock::Create(context, "", updateWorldFunc);
    BasicBlock *bBlock49  = BasicBlock::Create(context, "", updateWorldFunc);
    BasicBlock *bBlock53  = BasicBlock::Create(context, "", updateWorldFunc);
    BasicBlock *bBlock58  = BasicBlock::Create(context, "", updateWorldFunc);
    BasicBlock *bBlock61  = BasicBlock::Create(context, "", updateWorldFunc);
    BasicBlock *bBlock67  = BasicBlock::Create(context, "", updateWorldFunc);
    BasicBlock *bBlock71  = BasicBlock::Create(context, "", updateWorldFunc);

    Value *value0 = updateWorldFunc->getArg(0);
    Value *value1 = updateWorldFunc->getArg(1);

    // 0:
    builder.SetInsertPoint(bBlock0);

    // br label %3
    builder.CreateBr(bBlock3);

    // 3:
    builder.SetInsertPoint(bBlock3);

    //   %4 = phi i64 [ 0, %2 ], [ %8, %19 ]

    //   %5 = trunc i64 %4 to i32

    //   %6 = add i32 %5, -1

    //   %7 = icmp ugt i32 %6, 49

    //   %8 = add nuw nsw i64 %4, 1

    //   %9 = icmp ugt i64 %4, 48

    //   %10 = mul nuw nsw i64 %4, 50

    //   %11 = getelementptr inbounds i8, i8* %0, i64 %10

    //   %12 = getelementptr inbounds i8, i8* %1, i64 %10

    //   %13 = zext i32 %6 to i64

    //   %14 = mul nuw nsw i64 %13, 50

    //   %15 = getelementptr inbounds i8, i8* %0, i64 %14

    //   %16 = mul nuw nsw i64 %8, 50

    //   %17 = getelementptr inbounds i8, i8* %0, i64 %16

    //   br label %21
    builder.CreateBr(bBlock21);

    // 18:
    builder.SetInsertPoint(bBlock18);

    //   ret void
    builder.CreateRetVoid();

    // 19:
    builder.SetInsertPoint(bBlock19);

    //   %20 = icmp eq i64 %8, 50

    //   br i1 %20, label %18, label %3, !llvm.loop !13

    // 21:
    builder.SetInsertPoint(bBlock21);

    //   %22 = phi i64 [ 0, %3 ], [ %43, %71 ]

    //   %23 = trunc i64 %22 to i32

    //   %24 = add i32 %23, -1

    //   %25 = icmp ugt i32 %24, 49

    //   %26 = or i1 %7, %25

    //   br i1 %26, label %33, label %27

    // 27:
    builder.SetInsertPoint(bBlock27);

    //   %28 = zext i32 %24 to i64

    //   %29 = getelementptr inbounds i8, i8* %15, i64 %28

    //   %30 = load i8, i8* %29, align 1, !tbaa !7, !range !12

    //   %31 = mul nuw nsw i8 %30, 3

    //   %32 = zext i8 %31 to i32

    //   br label %33
    builder.CreateBr(bBlock33);

    // 33:
    builder.SetInsertPoint(bBlock33);

    //   %34 = phi i32 [ %32, %27 ], [ 0, %21 ]

    //   br i1 %25, label %40, label %35

    // 35:
    builder.SetInsertPoint(bBlock35);

    //   %36 = zext i32 %24 to i64

    //   %37 = getelementptr inbounds i8, i8* %11, i64 %36

    //   %38 = load i8, i8* %37, align 1, !tbaa !7, !range !12

    //   %39 = zext i8 %38 to i32

    //   br label %40
    builder.CreateBr(bBlock40);

    // 40:
    builder.SetInsertPoint(bBlock40);

    //   %41 = phi i32 [ %39, %35 ], [ 0, %33 ]

    //   %42 = add nuw nsw i32 %41, %34

    //   %43 = add nuw nsw i64 %22, 1

    //   %44 = icmp ugt i64 %22, 48

    //   br i1 %44, label %49, label %45

    // 45:
    builder.SetInsertPoint(bBlock45);

    //   %46 = getelementptr inbounds i8, i8* %11, i64 %43

    //   %47 = load i8, i8* %46, align 1, !tbaa !7, !range !12

    //   %48 = zext i8 %47 to i32

    //   br label %49
    builder.CreateBr(bBlock49);

    // 49:
    builder.SetInsertPoint(bBlock49);

    //   %50 = phi i32 [ %48, %45 ], [ 0, %40 ]

    //   %51 = add nuw nsw i32 %42, %50

    //   %52 = or i1 %9, %25

    //   br i1 %52, label %58, label %53

    // 53:
    builder.SetInsertPoint(bBlock53);

    //   %54 = zext i32 %24 to i64

    //   %55 = getelementptr inbounds i8, i8* %17, i64 %54

    //   %56 = load i8, i8* %55, align 1, !tbaa !7, !range !12

    //   %57 = zext i8 %56 to i32

    //   br label %58
    builder.CreateBr(bBlock58);

    // 58:
    builder.SetInsertPoint(bBlock58);

    //   %59 = phi i32 [ %57, %53 ], [ 0, %49 ]

    //   %60 = add nuw nsw i32 %51, %59

    //   br i1 %9, label %71, label %61

    // 61:
    builder.SetInsertPoint(bBlock61);

    //   %62 = getelementptr inbounds i8, i8* %17, i64 %22

    //   %63 = load i8, i8* %62, align 1, !tbaa !7, !range !12

    //   %64 = zext i8 %63 to i32

    //   %65 = add nuw nsw i32 %60, %64

    //   %66 = or i1 %9, %44

    //   br i1 %66, label %71, label %67

    // 67:
    builder.SetInsertPoint(bBlock67);

    //   %68 = getelementptr inbounds i8, i8* %17, i64 %43

    //   %69 = load i8, i8* %68, align 1, !tbaa !7, !range !12

    //   %70 = zext i8 %69 to i32

    //   br label %71
    builder.CreateBr(bBlock71);

    // 71:
    builder.SetInsertPoint(bBlock71);

    //   %72 = phi i32 [ %65, %67 ], [ %65, %61 ], [ %60, %58 ]

    //   %73 = phi i32 [ %70, %67 ], [ 0, %61 ], [ 0, %58 ]

    //   %74 = add nuw nsw i32 %72, %73

    //   %75 = getelementptr inbounds i8, i8* %11, i64 %22

    //   %76 = load i8, i8* %75, align 1, !tbaa !7, !range !12

    //   %77 = icmp eq i8 %76, 0

    //   %78 = getelementptr inbounds i8, i8* %12, i64 %22

    //   %79 = and i32 %74, -2

    //   %80 = icmp eq i32 %79, 2

    //   %81 = icmp ugt i32 %74, 2

    //   %82 = select i1 %77, i1 %81, i1 %80

    //   %83 = zext i1 %82 to i8

    //   store i8 %83, i8* %78, align 1, !tbaa !7

    //   %84 = icmp eq i64 %43, 50

    //   br i1 %84, label %19, label %21, !llvm.loop !14

    /*
      Now resolve all PHI nodes
    */

    value16->addIncoming(value14, bBlock7);
    value16->addIncoming(builder.getInt64(0), bBlock3);

    value16->addIncoming(value14, bBlock7);
    value16->addIncoming(builder.getInt64(0), bBlock3);

    value16->addIncoming(value14, bBlock7);
    value16->addIncoming(builder.getInt64(0), bBlock3);

    value16->addIncoming(value14, bBlock7);
    value16->addIncoming(builder.getInt64(0), bBlock3);

    value16->addIncoming(value14, bBlock7);
    value16->addIncoming(builder.getInt64(0), bBlock3);

    value16->addIncoming(value14, bBlock7);
    value16->addIncoming(builder.getInt64(0), bBlock3);

    value16->addIncoming(value14, bBlock7);
    value16->addIncoming(builder.getInt64(0), bBlock3);

    value16->addIncoming(value14, bBlock7);
    value16->addIncoming(builder.getInt64(0), bBlock3);
  }

  /*
    Actual IR for app() function
  */
  {
    // Declare all basic blocks in advance
    BasicBlock *bBlock0   = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock7   = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock15  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock8   = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock10  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock11  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock15  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock18  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock19  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock21  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock27  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock33  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock35  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock36  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock38  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock40  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock45  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock46  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock49  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock52  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock53  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock54  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock58  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock59  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock61  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock64  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock67  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock68  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock71  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock72  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock77  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock80  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock85  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock89  = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock103 = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock104 = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock119 = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock121 = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock127 = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock133 = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock135 = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock140 = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock145 = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock149 = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock153 = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock158 = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock161 = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock166 = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock170 = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock184 = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock185 = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock271 = BasicBlock::Create(context, "", appFunc);
    // BasicBlock *bBlock274 = BasicBlock::Create(context, "", appFunc);

    // 0:
    builder.SetInsertPoint(bBlock0);
    //   %1 = alloca [2500 x i8], align 16
    //   %2 = alloca [2500 x i8], align 16
    //   %3 = getelementptr inbounds [2500 x i8], [2500 x i8]* %2, i64 0, i64 0
    //   br label %4
    builder.CreateBr(bBlock4);

    // 4:                                                ; preds = %8, %0
    //   %5 = phi i64 [ 0, %0 ], [ %9, %8 ]
    //   %6 = mul nuw nsw i64 %5, 50
    //   %7 = getelementptr inbounds [2500 x i8], [2500 x i8]* %1, i64 0, i64 %6
    //   br label %11
    builder.CreateBr(bBlock11);

    // 8:                                                ; preds = %11
    //   %9 = add nuw nsw i64 %5, 1
    //   %10 = icmp eq i64 %9, 50
    //   br i1 %10, label %19, label %4, !llvm.loop !5

    // 11:                                               ; preds = %11, %4
    //   %12 = phi i64 [ 0, %4 ], [ %17, %11 ]
    //   %13 = tail call i32 @rand() #6
    //   %14 = getelementptr inbounds i8, i8* %7, i64 %12
    //   %15 = trunc i32 %13 to i8
    //   %16 = and i8 %15, 1
    //   store i8 %16, i8* %14, align 1, !tbaa !7
    //   %17 = add nuw nsw i64 %12, 1
    //   %18 = icmp eq i64 %17, 50
    //   br i1 %18, label %8, label %11, !llvm.loop !11

    // 19:                                               ; preds = %8
    //   %20 = getelementptr inbounds [2500 x i8], [2500 x i8]* %1, i64 0, i64 0
    //   call void @drawWorld(i8* noundef nonnull %20) #6
    //   br label %21
    builder.CreateBr(bBlock21);

    // 21:                                               ; preds = %38, %19
    //   %22 = phi i64 [ 0, %19 ], [ %39, %38 ]
    //   %23 = trunc i64 %22 to i32
    //   %24 = add i32 %23, -1
    //   %25 = icmp ugt i32 %24, 49
    //   %26 = add nuw nsw i64 %22, 1
    //   %27 = icmp ugt i64 %22, 48
    //   %28 = mul nuw nsw i64 %22, 50
    //   %29 = getelementptr inbounds [2500 x i8], [2500 x i8]* %1, i64 0, i64 %28
    //   %30 = getelementptr inbounds [2500 x i8], [2500 x i8]* %2, i64 0, i64 %28
    //   %31 = zext i32 %24 to i64
    //   %32 = mul nuw nsw i64 %31, 50
    //   %33 = getelementptr inbounds [2500 x i8], [2500 x i8]* %1, i64 0, i64 %32
    //   %34 = mul nuw nsw i64 %26, 50
    //   %35 = getelementptr inbounds [2500 x i8], [2500 x i8]* %1, i64 0, i64 %34
    //   br label %40
    builder.CreateBr(bBlock40);

    // 36:                                               ; preds = %89
    //   %37 = icmp eq i64 %26, 50
    //   br i1 %37, label %103, label %38

    // 38:                                               ; preds = %36, %235
    //   %39 = phi i64 [ %26, %36 ], [ 0, %235 ]
    //   br label %21, !llvm.loop !13

    // 40:                                               ; preds = %89, %21
    //   %41 = phi i64 [ 0, %21 ], [ %62, %89 ]
    //   %42 = trunc i64 %41 to i32
    //   %43 = add i32 %42, -1
    //   %44 = icmp ugt i32 %43, 49
    //   %45 = or i1 %25, %44
    //   br i1 %45, label %52, label %46

    // 46:                                               ; preds = %40
    //   %47 = zext i32 %43 to i64
    //   %48 = getelementptr inbounds i8, i8* %33, i64 %47
    //   %49 = load i8, i8* %48, align 1, !tbaa !7, !range !12
    //   %50 = mul nuw nsw i8 %49, 3
    //   %51 = zext i8 %50 to i32
    //   br label %52
    builder.CreateBr(bBlock52);

    // 52:                                               ; preds = %46, %40
    //   %53 = phi i32 [ %51, %46 ], [ 0, %40 ]
    //   br i1 %44, label %59, label %54

    // 54:                                               ; preds = %52
    //   %55 = zext i32 %43 to i64
    //   %56 = getelementptr inbounds i8, i8* %29, i64 %55
    //   %57 = load i8, i8* %56, align 1, !tbaa !7, !range !12
    //   %58 = zext i8 %57 to i32
    //   br label %59
    builder.CreateBr(bBlock15);

    // 59:                                               ; preds = %54, %52
    //   %60 = phi i32 [ %58, %54 ], [ 0, %52 ]
    //   %61 = add nuw nsw i32 %60, %53
    //   %62 = add nuw nsw i64 %41, 1
    //   %63 = icmp ugt i64 %41, 48
    //   br i1 %63, label %68, label %64

    // 64:                                               ; preds = %59
    //   %65 = getelementptr inbounds i8, i8* %29, i64 %62
    //   %66 = load i8, i8* %65, align 1, !tbaa !7, !range !12
    //   %67 = zext i8 %66 to i32
    //   br label %68

    // 68:                                               ; preds = %64, %59
    //   %69 = phi i32 [ %67, %64 ], [ 0, %59 ]
    //   %70 = add nuw nsw i32 %61, %69
    //   %71 = or i1 %27, %44
    //   br i1 %71, label %77, label %72

    // 72:                                               ; preds = %68
    //   %73 = zext i32 %43 to i64
    //   %74 = getelementptr inbounds i8, i8* %35, i64 %73
    //   %75 = load i8, i8* %74, align 1, !tbaa !7, !range !12
    //   %76 = zext i8 %75 to i32
    //   br label %77

    // 77:                                               ; preds = %72, %68
    //   %78 = phi i32 [ %76, %72 ], [ 0, %68 ]
    //   %79 = add nuw nsw i32 %70, %78
    //   br i1 %27, label %89, label %80

    // 80:                                               ; preds = %77
    //   %81 = getelementptr inbounds i8, i8* %35, i64 %41
    //   %82 = load i8, i8* %81, align 1, !tbaa !7, !range !12
    //   %83 = zext i8 %82 to i32
    //   %84 = add nuw nsw i32 %79, %83
    //   br i1 %63, label %89, label %85

    // 85:                                               ; preds = %80
    //   %86 = getelementptr inbounds i8, i8* %35, i64 %62
    //   %87 = load i8, i8* %86, align 1, !tbaa !7, !range !12
    //   %88 = zext i8 %87 to i32
    //   br label %89

    // 89:                                               ; preds = %85, %80, %77
    //   %90 = phi i32 [ %84, %85 ], [ %84, %80 ], [ %79, %77 ]
    //   %91 = phi i32 [ %88, %85 ], [ 0, %80 ], [ 0, %77 ]
    //   %92 = add nuw nsw i32 %91, %90
    //   %93 = getelementptr inbounds i8, i8* %29, i64 %41
    //   %94 = load i8, i8* %93, align 1, !tbaa !7, !range !12
    //   %95 = icmp eq i8 %94, 0
    //   %96 = getelementptr inbounds i8, i8* %30, i64 %41
    //   %97 = and i32 %92, -2
    //   %98 = icmp eq i32 %97, 2
    //   %99 = icmp ugt i32 %92, 2
    //   %100 = select i1 %95, i1 %99, i1 %98
    //   %101 = zext i1 %100 to i8
    //   store i8 %101, i8* %96, align 1, !tbaa !7
    //   %102 = icmp eq i64 %62, 50
    //   br i1 %102, label %36, label %40, !llvm.loop !14

    // 103:                                              ; preds = %36
    //   call void @drawWorld(i8* noundef nonnull %3) #6
    //   br label %104

    // 104:                                              ; preds = %119, %103
    //   %105 = phi i64 [ 0, %103 ], [ %109, %119 ]
    //   %106 = trunc i64 %105 to i32
    //   %107 = add i32 %106, -1
    //   %108 = icmp ugt i32 %107, 49
    //   %109 = add nuw nsw i64 %105, 1
    //   %110 = icmp ugt i64 %105, 48
    //   %111 = mul nuw nsw i64 %105, 50
    //   %112 = getelementptr inbounds [2500 x i8], [2500 x i8]* %2, i64 0, i64 %111
    //   %113 = getelementptr inbounds [2500 x i8], [2500 x i8]* %1, i64 0, i64 %111
    //   %114 = zext i32 %107 to i64
    //   %115 = mul nuw nsw i64 %114, 50
    //   %116 = getelementptr inbounds [2500 x i8], [2500 x i8]* %2, i64 0, i64 %115
    //   %117 = mul nuw nsw i64 %109, 50
    //   %118 = getelementptr inbounds [2500 x i8], [2500 x i8]* %2, i64 0, i64 %117
    //   br label %121

    // 119:                                              ; preds = %170
    //   %120 = icmp eq i64 %109, 50
    //   br i1 %120, label %184, label %104, !llvm.loop !13

    // 121:                                              ; preds = %170, %104
    //   %122 = phi i64 [ 0, %104 ], [ %143, %170 ]
    //   %123 = trunc i64 %122 to i32
    //   %124 = add i32 %123, -1
    //   %125 = icmp ugt i32 %124, 49
    //   %126 = or i1 %108, %125
    //   br i1 %126, label %133, label %127

    // 127:                                              ; preds = %121
    //   %128 = zext i32 %124 to i64
    //   %129 = getelementptr inbounds i8, i8* %116, i64 %128
    //   %130 = load i8, i8* %129, align 1, !tbaa !7, !range !12
    //   %131 = mul nuw nsw i8 %130, 3
    //   %132 = zext i8 %131 to i32
    //   br label %133

    // 133:                                              ; preds = %127, %121
    //   %134 = phi i32 [ %132, %127 ], [ 0, %121 ]
    //   br i1 %125, label %140, label %135

    // 135:                                              ; preds = %133
    //   %136 = zext i32 %124 to i64
    //   %137 = getelementptr inbounds i8, i8* %112, i64 %136
    //   %138 = load i8, i8* %137, align 1, !tbaa !7, !range !12
    //   %139 = zext i8 %138 to i32
    //   br label %140

    // 140:                                              ; preds = %135, %133
    //   %141 = phi i32 [ %139, %135 ], [ 0, %133 ]
    //   %142 = add nuw nsw i32 %141, %134
    //   %143 = add nuw nsw i64 %122, 1
    //   %144 = icmp ugt i64 %122, 48
    //   br i1 %144, label %149, label %145

    // 145:                                              ; preds = %140
    //   %146 = getelementptr inbounds i8, i8* %112, i64 %143
    //   %147 = load i8, i8* %146, align 1, !tbaa !7, !range !12
    //   %148 = zext i8 %147 to i32
    //   br label %149

    // 149:                                              ; preds = %145, %140
    //   %150 = phi i32 [ %148, %145 ], [ 0, %140 ]
    //   %151 = add nuw nsw i32 %142, %150
    //   %152 = or i1 %110, %125
    //   br i1 %152, label %158, label %153

    // 153:                                              ; preds = %149
    //   %154 = zext i32 %124 to i64
    //   %155 = getelementptr inbounds i8, i8* %118, i64 %154
    //   %156 = load i8, i8* %155, align 1, !tbaa !7, !range !12
    //   %157 = zext i8 %156 to i32
    //   br label %158

    // 158:                                              ; preds = %153, %149
    //   %159 = phi i32 [ %157, %153 ], [ 0, %149 ]
    //   %160 = add nuw nsw i32 %151, %159
    //   br i1 %110, label %170, label %161

    // 161:                                              ; preds = %158
    //   %162 = getelementptr inbounds i8, i8* %118, i64 %122
    //   %163 = load i8, i8* %162, align 1, !tbaa !7, !range !12
    //   %164 = zext i8 %163 to i32
    //   %165 = add nuw nsw i32 %160, %164
    //   br i1 %144, label %170, label %166

    // 166:                                              ; preds = %161
    //   %167 = getelementptr inbounds i8, i8* %118, i64 %143
    //   %168 = load i8, i8* %167, align 1, !tbaa !7, !range !12
    //   %169 = zext i8 %168 to i32
    //   br label %170

    // 170:                                              ; preds = %166, %161, %158
    //   %171 = phi i32 [ %165, %166 ], [ %165, %161 ], [ %160, %158 ]
    //   %172 = phi i32 [ %169, %166 ], [ 0, %161 ], [ 0, %158 ]
    //   %173 = add nuw nsw i32 %172, %171
    //   %174 = getelementptr inbounds i8, i8* %112, i64 %122
    //   %175 = load i8, i8* %174, align 1, !tbaa !7, !range !12
    //   %176 = icmp eq i8 %175, 0
    //   %177 = getelementptr inbounds i8, i8* %113, i64 %122
    //   %178 = and i32 %173, -2
    //   %179 = icmp eq i32 %178, 2
    //   %180 = icmp ugt i32 %173, 2
    //   %181 = select i1 %176, i1 %180, i1 %179
    //   %182 = zext i1 %181 to i8
    //   store i8 %182, i8* %177, align 1, !tbaa !7
    //   %183 = icmp eq i64 %143, 50
    //   br i1 %183, label %119, label %121, !llvm.loop !14

    // 184:                                              ; preds = %119
    //   call void @drawWorld(i8* noundef nonnull %20) #6
    //   br label %185

    // 185:                                              ; preds = %184, %185
    //   %186 = phi i64 [ 0, %184 ], [ %233, %185 ]
    //   %187 = phi i8 [ 1, %184 ], [ %232, %185 ]
    //   %188 = mul nuw nsw i64 %186, 50
    //   %189 = getelementptr inbounds [2500 x i8], [2500 x i8]* %1, i64 0, i64 %188
    //   %190 = getelementptr inbounds [2500 x i8], [2500 x i8]* %2, i64 0, i64 %188
    //   %191 = getelementptr inbounds i8, i8* %189, i64 32
    //   %192 = bitcast i8* %191 to <16 x i8>*
    //   %193 = load <16 x i8>, <16 x i8>* %192, align 2, !tbaa !7
    //   %194 = getelementptr inbounds i8, i8* %190, i64 32
    //   %195 = bitcast i8* %194 to <16 x i8>*
    //   %196 = load <16 x i8>, <16 x i8>* %195, align 2, !tbaa !7
    //   %197 = icmp eq <16 x i8> %193, %196
    //   %198 = getelementptr inbounds i8, i8* %189, i64 16
    //   %199 = bitcast i8* %198 to <16 x i8>*
    //   %200 = load <16 x i8>, <16 x i8>* %199, align 2, !tbaa !7
    //   %201 = getelementptr inbounds i8, i8* %190, i64 16
    //   %202 = bitcast i8* %201 to <16 x i8>*
    //   %203 = load <16 x i8>, <16 x i8>* %202, align 2, !tbaa !7
    //   %204 = icmp eq <16 x i8> %200, %203
    //   %205 = select <16 x i1> %197, <16 x i1> %204, <16 x i1> zeroinitializer
    //   %206 = bitcast i8* %189 to <16 x i8>*
    //   %207 = load <16 x i8>, <16 x i8>* %206, align 2, !tbaa !7
    //   %208 = bitcast i8* %190 to <16 x i8>*
    //   %209 = load <16 x i8>, <16 x i8>* %208, align 2, !tbaa !7
    //   %210 = icmp eq <16 x i8> %207, %209
    //   %211 = select <16 x i1> %205, <16 x i1> %210, <16 x i1> zeroinitializer
    //   %212 = insertelement <16 x i8> poison, i8 %187, i64 0
    //   %213 = shufflevector <16 x i8> %212, <16 x i8> poison, <16 x i32> zeroinitializer
    //   %214 = select <16 x i1> %211, <16 x i8> %213, <16 x i8> zeroinitializer
    //   %215 = insertelement <16 x i8> poison, i8 %187, i64 0
    //   %216 = shufflevector <16 x i8> %215, <16 x i8> poison, <16 x i32> zeroinitializer
    //   %217 = icmp ne <16 x i8> %214, %216
    //   %218 = bitcast <16 x i1> %217 to i16
    //   %219 = icmp eq i16 %218, 0
    //   %220 = getelementptr inbounds i8, i8* %189, i64 48
    //   %221 = load i8, i8* %220, align 2, !tbaa !7, !range !12
    //   %222 = getelementptr inbounds i8, i8* %190, i64 48
    //   %223 = load i8, i8* %222, align 2, !tbaa !7, !range !12
    //   %224 = icmp eq i8 %221, %223
    //   %225 = getelementptr inbounds i8, i8* %189, i64 49
    //   %226 = load i8, i8* %225, align 1, !tbaa !7, !range !12
    //   %227 = getelementptr inbounds i8, i8* %190, i64 49
    //   %228 = load i8, i8* %227, align 1, !tbaa !7, !range !12
    //   %229 = icmp eq i8 %226, %228
    //   %230 = select i1 %229, i1 %224, i1 false
    //   %231 = select i1 %230, i1 %219, i1 false
    //   %232 = select i1 %231, i8 %187, i8 0
    //   %233 = add nuw nsw i64 %186, 1
    //   %234 = icmp eq i64 %233, 50
    //   br i1 %234, label %235, label %185, !llvm.loop !15

    // 235:                                              ; preds = %185
    //   %236 = and i8 %232, 1
    //   %237 = icmp eq i8 %236, 0
    //   br i1 %237, label %38, label %238

    // 238:                                              ; preds = %235
    //   ret void
    builder.CreateRetVoid();

  }

  // Dump LLVM IR
  module->print(outs(), nullptr);

  // Interpreter of LLVM IR
  outs() << "Running code...\n";
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();

  ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
  ee->InstallLazyFunctionCreator([&](const std::string &fnName) -> void * {
			if (fnName == "drawWorld") {
				return reinterpret_cast<void *>(drawWorld);
			}
			return nullptr;
		});
  ee->finalizeObject();

  renderer = createRenderer();

  ArrayRef<GenericValue> noargs;
  GenericValue v = ee->runFunction(appFunc, noargs);
  outs() << "Code was run.\n";

  stopDrawing();
  return 0;
}
