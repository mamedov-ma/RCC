#include "../include/game_of_life.h"
#include <SDL2/SDL.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

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

int rand()
{
  return rand();
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

  ArrayType::Type *arrayType = ArrayType::get(builder.getInt8Ty(), 2500);
  VectorType::Type *intVector = VectorType::get(builder.getInt32Ty(), 16, false);
  VectorType::Type *byteVector = VectorType::get(builder.getInt8Ty(), 16, false);
  VectorType::Type *bitVector = VectorType::get(builder.getInt1Ty(), 16, false);

  Align align16 = Align(16);
  Align align8  = Align(8);
  Align align4  = Align(4);
  Align align2  = Align(2);
  Align align1  = Align(1);

  /*
    Declare external functions
  */

  // declare void @drawWorld(i8* noundef) local_unnamed_addr #5
  FunctionType *drawWorldFuncType = FunctionType::get(builder.getVoidTy(), {builder.getInt8PtrTy()}, false);
  FunctionCallee drawWorldFunc = module->getOrInsertFunction("drawWorld", drawWorldFuncType);

  // declare i32 @rand() local_unnamed_addr #1
  FunctionType *randFuncType = FunctionType::get(builder.getInt32Ty(), false);
  FunctionCallee randFunc = module->getOrInsertFunction("rand", randFuncType);

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
  FunctionType *updateCellFuncType = FunctionType::get(builder.getVoidTy(), {builder.getInt1Ty(), builder.getInt8PtrTy(), builder.getInt32Ty()}, false);
  Function *updateCellFunc = Function::Create(updateCellFuncType, Function::ExternalLinkage, "updateCell", module);
  updateCellFunc->setDSOLocal(true);
  updateCellFunc->setUnnamedAddr(GlobalValue::UnnamedAddr::Local);

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
    BasicBlock *bBlock1   = BasicBlock::Create(context, "", generateWorldFunc);
    BasicBlock *bBlock2   = BasicBlock::Create(context, "", generateWorldFunc);
    BasicBlock *bBlock3   = BasicBlock::Create(context, "", generateWorldFunc);
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
    Value *value5 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value0, value4);

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
    BasicBlock *bBlock3   = BasicBlock::Create(context, "", toUintFunc);
    BasicBlock *bBlock7   = BasicBlock::Create(context, "", toUintFunc);
    BasicBlock *bBlock15  = BasicBlock::Create(context, "", toUintFunc);

    Value *value0 = toUintFunc->getArg(0);
    Value *value1 = toUintFunc->getArg(1);
    Value *value2 = toUintFunc->getArg(2);

    // 0:
    builder.SetInsertPoint(bBlock0);

    // %4 = icmp ugt i32 %2, 49
    Value *value4 = builder.CreateICmpUGT(value2, builder.getInt32(49));

    // %5 = icmp ugt i32 %1, 49
    Value *value5 = builder.CreateICmpUGT(value1, builder.getInt32(49));

    // %6 = or i1 %5, %4
    Value *value6 = builder.CreateOr(value5, value4);

    // br i1 %6, label %15, label %7
    builder.CreateCondBr(value6, bBlock15, bBlock7);

    // 7:
    builder.SetInsertPoint(bBlock7);

    // %8 = zext i32 %1 to i64
    Value *value8 = builder.CreateZExt(value1, builder.getInt64Ty());

    // %9 = mul nuw nsw i64 %8, 50
    Value *value9 = builder.CreateMul(value8, builder.getInt64(50), "", true, true);

    // %10 = getelementptr inbounds i8, i8* %0, i64 %9
    Value *value10 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value0, value9);

    // %11 = zext i32 %2 to i64
    Value *value11 = builder.CreateZExt(value2, builder.getInt64Ty());

    // %12 = getelementptr inbounds i8, i8* %10, i64 %11
    Value *value12 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value10, value11);

    // %13 = load i8, i8* %12, align 1, !tbaa !7, !range !12
    Value *value13 = builder.CreateAlignedLoad(builder.getInt8Ty(), value12, align1);

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
    value16->addIncoming(builder.getInt32(0), bBlock3);
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
    Value *value4 = builder.CreateFAdd(value2, builder.getInt32(-2));

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
    BasicBlock *bBlock2   = BasicBlock::Create(context, "", updateWorldFunc);
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
    PHINode *value4 = builder.CreatePHI(builder.getInt64Ty(), 2);

    //   %5 = trunc i64 %4 to i32
    Value *value5 = builder.CreateTrunc(value4, builder.getInt32Ty());

    //   %6 = add i32 %5, -1
    Value *value6 = builder.CreateAdd(value5, builder.getInt32(-1));

    //   %7 = icmp ugt i32 %6, 49
    Value *value7 = builder.CreateICmpUGT(value6, builder.getInt32(49));

    //   %8 = add nuw nsw i64 %4, 1
    Value *value8 = builder.CreateAdd(value4, builder.getInt64(1), "", true, true);

    //   %9 = icmp ugt i64 %4, 48
    Value *value9 = builder.CreateICmpUGT(value4, builder.getInt64(48));

    //   %10 = mul nuw nsw i64 %4, 50
    Value *value10 = builder.CreateMul(value4, builder.getInt64(50), "", true, true);

    //   %11 = getelementptr inbounds i8, i8* %0, i64 %10
    Value *value11 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value0, value10);

    //   %12 = getelementptr inbounds i8, i8* %1, i64 %10
    Value *value12 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value1, value10);

    //   %13 = zext i32 %6 to i64
    Value *value13 = builder.CreateZExt(value6, builder.getInt64Ty());

    //   %14 = mul nuw nsw i64 %13, 50
    Value *value14 = builder.CreateMul(value13, builder.getInt64(50), "", true, true);

    //   %15 = getelementptr inbounds i8, i8* %0, i64 %14
    Value *value15 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value0, value14);

    //   %16 = mul nuw nsw i64 %8, 50
    Value *value16 = builder.CreateMul(value8, builder.getInt64(50), "", true, true);

    //   %17 = getelementptr inbounds i8, i8* %0, i64 %16
    Value *value17 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value0, value16);

    //   br label %21
    builder.CreateBr(bBlock21);

    // 18:
    builder.SetInsertPoint(bBlock18);

    //   ret void
    builder.CreateRetVoid();

    // 19:
    builder.SetInsertPoint(bBlock19);

    //   %20 = icmp eq i64 %8, 50
    Value *value20 = builder.CreateICmpEQ(value8, builder.getInt64(50));

    //   br i1 %20, label %18, label %3, !llvm.loop !13
    builder.CreateCondBr(value20, bBlock18, bBlock3);

    // 21:
    builder.SetInsertPoint(bBlock21);

    //   %22 = phi i64 [ 0, %3 ], [ %43, %71 ]
    PHINode *value22 = builder.CreatePHI(builder.getInt64Ty(), 2);

    //   %23 = trunc i64 %22 to i32
    Value *value23 = builder.CreateTrunc(value22, builder.getInt32Ty());

    //   %24 = add i32 %23, -1
    Value *value24 = builder.CreateAdd(value23, builder.getInt32(-1));

    //   %25 = icmp ugt i32 %24, 49
    Value *value25 = builder.CreateICmpUGT(value24, builder.getInt32(49));

    //   %26 = or i1 %7, %25
    Value *value26 = builder.CreateOr(value7, value25);

    //   br i1 %26, label %33, label %27
    builder.CreateCondBr(value26, bBlock33, bBlock27);

    // 27:
    builder.SetInsertPoint(bBlock27);

    //   %28 = zext i32 %24 to i64
    Value *value28 = builder.CreateZExt(value24, builder.getInt64Ty());

    //   %29 = getelementptr inbounds i8, i8* %15, i64 %28
    Value *value29 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value15, value28);

    //   %30 = load i8, i8* %29, align 1, !tbaa !7, !range !12
    Value *value30 = builder.CreateAlignedLoad(builder.getInt8Ty(), value29, align1);

    //   %31 = mul nuw nsw i8 %30, 3
    Value *value31 = builder.CreateMul(value30, builder.getInt8(3), "", true, true);

    //   %32 = zext i8 %31 to i32
    Value *value32 = builder.CreateZExt(value31, builder.getInt32Ty());

    //   br label %33
    builder.CreateBr(bBlock33);

    // 33:
    builder.SetInsertPoint(bBlock33);

    //   %34 = phi i32 [ %32, %27 ], [ 0, %21 ]
    PHINode *value34 = builder.CreatePHI(builder.getInt32Ty(), 2);

    //   br i1 %25, label %40, label %35
    builder.CreateCondBr(value25, bBlock40, bBlock35);

    // 35:
    builder.SetInsertPoint(bBlock35);

    //   %36 = zext i32 %24 to i64
    Value *value36 = builder.CreateZExt(value24, builder.getInt64Ty());

    //   %37 = getelementptr inbounds i8, i8* %11, i64 %36
    Value *value37 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value11, value36);

    //   %38 = load i8, i8* %37, align 1, !tbaa !7, !range !12
    Value *value38 = builder.CreateAlignedLoad(builder.getInt8Ty(), value37, align1);

    //   %39 = zext i8 %38 to i32
    Value *value39 = builder.CreateZExt(value38, builder.getInt32Ty());

    //   br label %40
    builder.CreateBr(bBlock40);

    // 40:
    builder.SetInsertPoint(bBlock40);

    //   %41 = phi i32 [ %39, %35 ], [ 0, %33 ]
    PHINode *value41 = builder.CreatePHI(builder.getInt32Ty(), 2);

    //   %42 = add nuw nsw i32 %41, %34
    Value *value42 = builder.CreateAdd(value41, value34, "", true, true);

    //   %43 = add nuw nsw i64 %22, 1
    Value *value43 = builder.CreateAdd(value22, builder.getInt64(1), "", true, true);

    //   %44 = icmp ugt i64 %22, 48
    Value *value44 = builder.CreateICmpUGT(value22, builder.getInt64(48));

    //   br i1 %44, label %49, label %45
    builder.CreateCondBr(value44, bBlock49, bBlock45);

    // 45:
    builder.SetInsertPoint(bBlock45);

    //   %46 = getelementptr inbounds i8, i8* %11, i64 %43
    Value *value46 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value11, value43);

    //   %47 = load i8, i8* %46, align 1, !tbaa !7, !range !12
    Value *value47 = builder.CreateAlignedLoad(builder.getInt8Ty(), value46, align1);

    //   %48 = zext i8 %47 to i32
    Value *value48 = builder.CreateZExt(value47, builder.getInt32Ty());

    //   br label %49
    builder.CreateBr(bBlock49);

    // 49:
    builder.SetInsertPoint(bBlock49);

    //   %50 = phi i32 [ %48, %45 ], [ 0, %40 ]
    PHINode *value50 = builder.CreatePHI(builder.getInt32Ty(), 2);

    //   %51 = add nuw nsw i32 %42, %50
    Value *value51 = builder.CreateAdd(value42, value50, "", true, true);

    //   %52 = or i1 %9, %25
    Value *value52 = builder.CreateOr(value9, value25);

    //   br i1 %52, label %58, label %53
    builder.CreateCondBr(value52, bBlock58, bBlock53);

    // 53:
    builder.SetInsertPoint(bBlock53);

    //   %54 = zext i32 %24 to i64
    Value *value54 = builder.CreateZExt(value24, builder.getInt32Ty());

    //   %55 = getelementptr inbounds i8, i8* %17, i64 %54
    Value *value55 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value17, value54);

    //   %56 = load i8, i8* %55, align 1, !tbaa !7, !range !12
    Value *value56 = builder.CreateAlignedLoad(builder.getInt8Ty(), value55, align1);

    //   %57 = zext i8 %56 to i32
    Value *value57 = builder.CreateZExt(value56, builder.getInt32Ty());

    //   br label %58
    builder.CreateBr(bBlock58);

    // 58:
    builder.SetInsertPoint(bBlock58);

    //   %59 = phi i32 [ %57, %53 ], [ 0, %49 ]
    PHINode *value59 = builder.CreatePHI(builder.getInt32Ty(), 2);

    //   %60 = add nuw nsw i32 %51, %59
    Value *value60 = builder.CreateAdd(value51, value59, "", true, true);

    //   br i1 %9, label %71, label %61
    builder.CreateCondBr(value9, bBlock71, bBlock61);

    // 61:
    builder.SetInsertPoint(bBlock61);

    //   %62 = getelementptr inbounds i8, i8* %17, i64 %22
    Value *value62 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value17, value22);

    //   %63 = load i8, i8* %62, align 1, !tbaa !7, !range !12
    Value *value63 = builder.CreateAlignedLoad(builder.getInt8Ty(), value62, align1);

    //   %64 = zext i8 %63 to i32
    Value *value64 = builder.CreateZExt(value63, builder.getInt32Ty());

    //   %65 = add nuw nsw i32 %60, %64
    Value *value65 = builder.CreateAdd(value60, value64, "", true, true);

    //   %66 = or i1 %9, %44
    Value *value66 = builder.CreateOr(value9, value44);

    //   br i1 %66, label %71, label %67
    builder.CreateCondBr(value66, bBlock71, bBlock67);

    // 67:
    builder.SetInsertPoint(bBlock67);

    //   %68 = getelementptr inbounds i8, i8* %17, i64 %43
    Value *value68 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value17, value43);

    //   %69 = load i8, i8* %68, align 1, !tbaa !7, !range !12
    Value *value69 = builder.CreateAlignedLoad(builder.getInt8Ty(), value68, align1);

    //   %70 = zext i8 %69 to i32
    Value *value70 = builder.CreateZExt(value69, builder.getInt32Ty());

    //   br label %71
    builder.CreateBr(bBlock71);

    // 71:
    builder.SetInsertPoint(bBlock71);

    //   %72 = phi i32 [ %65, %67 ], [ %65, %61 ], [ %60, %58 ]
    PHINode *value72 = builder.CreatePHI(builder.getInt32Ty(), 3);

    //   %73 = phi i32 [ %70, %67 ], [ 0, %61 ], [ 0, %58 ]
    PHINode *value73 = builder.CreatePHI(builder.getInt32Ty(), 3);

    //   %74 = add nuw nsw i32 %72, %73
    Value *value74 = builder.CreateAdd(value72, value73, "", true, true);

    //   %75 = getelementptr inbounds i8, i8* %11, i64 %22
    Value *value75 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value11, value22);

    //   %76 = load i8, i8* %75, align 1, !tbaa !7, !range !12
    Value *value76 = builder.CreateAlignedLoad(builder.getInt8Ty(), value75, align1);

    //   %77 = icmp eq i8 %76, 0
    Value *value77 = builder.CreateICmpEQ(value76, builder.getInt8(0));

    //   %78 = getelementptr inbounds i8, i8* %12, i64 %22
    Value *value78 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value12, value22);

    //   %79 = and i32 %74, -2
    Value *value79 = builder.CreateFAdd(value74, builder.getInt32(-2));

    //   %80 = icmp eq i32 %79, 2
    Value *value80 = builder.CreateICmpEQ(value79, builder.getInt32(2));

    //   %81 = icmp ugt i32 %74, 2
    Value *value81 = builder.CreateICmpUGT(value74, builder.getInt32(2));

    //   %82 = select i1 %77, i1 %81, i1 %80
    Value *value82 = builder.CreateSelect(value77, value81, value80);

    //   %83 = zext i1 %82 to i8
    Value *value83 = builder.CreateZExt(value82, builder.getInt8Ty());

    //   store i8 %83, i8* %78, align 1, !tbaa !7
    builder.CreateAlignedStore(value83, value78, align1);

    //   %84 = icmp eq i64 %43, 50
    Value *value84 = builder.CreateICmpEQ(value43, builder.getInt64(50));

    //   br i1 %84, label %19, label %21, !llvm.loop !14
    builder.CreateCondBr(value84, bBlock19, bBlock21);

    /*
      Now resolve all PHI nodes
    */

    value4->addIncoming(builder.getInt64(0), bBlock2);
    value4->addIncoming(value8, bBlock19);

    value22->addIncoming(builder.getInt64(0), bBlock3);
    value22->addIncoming(value43, bBlock71);

    value34->addIncoming(value32, bBlock27);
    value34->addIncoming(builder.getInt32(0), bBlock21);

    value41->addIncoming(value39, bBlock35);
    value41->addIncoming(builder.getInt32(0), bBlock33);

    value50->addIncoming(value48, bBlock45);
    value50->addIncoming(builder.getInt32(0), bBlock40);

    value59->addIncoming(value57, bBlock53);
    value59->addIncoming(builder.getInt32(0), bBlock49);

    value72->addIncoming(value65, bBlock67);
    value72->addIncoming(value65, bBlock61);
    value72->addIncoming(value60, bBlock58);

    value73->addIncoming(value70, bBlock67);
    value73->addIncoming(builder.getInt32(0), bBlock61);
    value73->addIncoming(builder.getInt32(0), bBlock58);
  }

  /*
    Actual IR for app() function
  */
  {
    // Declare all basic blocks in advance
    BasicBlock *bBlock0   = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock4   = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock8   = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock11  = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock19  = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock21  = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock36  = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock38  = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock40  = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock46  = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock52  = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock54  = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock59  = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock64  = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock68  = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock72  = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock77  = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock80  = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock85  = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock89  = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock103 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock104 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock119 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock121 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock127 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock133 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock135 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock140 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock145 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock149 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock153 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock158 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock161 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock166 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock170 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock184 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock185 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock235 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *bBlock238 = BasicBlock::Create(context, "", appFunc);

    // 0:
    builder.SetInsertPoint(bBlock0);

    builder.SetInsertPoint(bBlock0);
    //   %1 = alloca [2500 x i8], align 16
    AllocaInst *value1 = builder.CreateAlloca(arrayType);
    value1->setAlignment(align16);

    //   %2 = alloca [2500 x i8], align 16
    AllocaInst *value2 = builder.CreateAlloca(arrayType);
    value1->setAlignment(align16);

    //   %3 = getelementptr inbounds [2500 x i8], [2500 x i8]* %2, i64 0, i64 0
    Value *value3 = builder.CreateInBoundsGEP(arrayType, value2, {builder.getInt64(0), builder.getInt64(0)});

    //   br label %4
    builder.CreateBr(bBlock4);

    // 4:
    builder.SetInsertPoint(bBlock4);

    //   %5 = phi i64 [ 0, %0 ], [ %9, %8 ]
    PHINode *value5 = builder.CreatePHI(builder.getInt64Ty(), 2);

    //   %6 = mul nuw nsw i64 %5, 50
    Value *value6 = builder.CreateMul(value5, builder.getInt64(50), "", true, true);

    //   %7 = getelementptr inbounds [2500 x i8], [2500 x i8]* %1, i64 0, i64 %6
    Value *value7 = builder.CreateInBoundsGEP(arrayType, value1, {builder.getInt64(0), value6});

    //   br label %11
    builder.CreateBr(bBlock11);

    // 8:
    builder.SetInsertPoint(bBlock8);

    //   %9 = add nuw nsw i64 %5, 1
    Value *value9 = builder.CreateAdd(value5, builder.getInt64(1), "", true, true);

    //   %10 = icmp eq i64 %9, 50
    Value *value10 = builder.CreateICmpEQ(value9, builder.getInt64(50));

    //   br i1 %10, label %19, label %4, !llvm.loop !5
    builder.CreateCondBr(value10, bBlock19, bBlock4);

    // 11:
    builder.SetInsertPoint(bBlock11);

    //   %12 = phi i64 [ 0, %4 ], [ %17, %11 ]
    PHINode *value12 = builder.CreatePHI(builder.getInt64Ty(), 2);

    //   %13 = tail call i32 @rand() #6
    CallInst *value13 = builder.CreateCall(randFunc);
    value13->setTailCall(true);

    //   %14 = getelementptr inbounds i8, i8* %7, i64 %12
    Value *value14 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value7, value12);

    //   %15 = trunc i32 %13 to i8
    Value *value15 = builder.CreateTrunc(value13, builder.getInt8Ty());

    //   %16 = and i8 %15, 1
    Value *value16 = builder.CreateFAdd(value15, builder.getInt8(1));

    //   store i8 %16, i8* %14, align 1, !tbaa !7
    builder.CreateAlignedStore(value16, value14, align1);

    //   %17 = add nuw nsw i64 %12, 1
    Value *value17 = builder.CreateAdd(value12, builder.getInt64(1), "", true, true);

    //   %18 = icmp eq i64 %17, 50
    Value *value18 = builder.CreateICmpEQ(value17, builder.getInt64(50));

    //   br i1 %18, label %8, label %11, !llvm.loop !11
    builder.CreateCondBr(value18, bBlock8, bBlock11);

    // 19:
    builder.SetInsertPoint(bBlock19);

    //   %20 = getelementptr inbounds [2500 x i8], [2500 x i8]* %1, i64 0, i64 0
    Value *value20 = builder.CreateInBoundsGEP(arrayType, value1, {builder.getInt64(0), builder.getInt64(0)});

    //   call void @drawWorld(i8* noundef nonnull %20) #6
    CallInst *call1 = builder.CreateCall(drawWorldFunc, {value20});
    call1->setTailCall(true);

    //   br label %21
    builder.CreateBr(bBlock21);

    // 21:
    builder.SetInsertPoint(bBlock21);

    //   %22 = phi i64 [ 0, %19 ], [ %39, %38 ]
    PHINode *value22 = builder.CreatePHI(builder.getInt64Ty(), 2);
    //   %23 = trunc i64 %22 to i32
    Value *value23 = builder.CreateTrunc(value22, builder.getInt32Ty());

    //   %24 = add i32 %23, -1
    Value *value24 = builder.CreateAdd(value23, builder.getInt32(-1));

    //   %25 = icmp ugt i32 %24, 49
    Value *value25 = builder.CreateICmpUGT(value24, builder.getInt32(49));

    //   %26 = add nuw nsw i64 %22, 1
    Value *value26 = builder.CreateAdd(value22, builder.getInt64(1), "", true, true);

    //   %27 = icmp ugt i64 %22, 48
    Value *value27 = builder.CreateICmpUGT(value22, builder.getInt64(48));

    //   %28 = mul nuw nsw i64 %22, 50
    Value *value28 = builder.CreateMul(value22, builder.getInt64(50), "", true, true);

    //   %29 = getelementptr inbounds [2500 x i8], [2500 x i8]* %1, i64 0, i64 %28
    Value *value29 = builder.CreateInBoundsGEP(arrayType, value1, {builder.getInt64(0), value28});

    //   %30 = getelementptr inbounds [2500 x i8], [2500 x i8]* %2, i64 0, i64 %28
    Value *value30 = builder.CreateInBoundsGEP(arrayType, value2, {builder.getInt64(0), value28});

    //   %31 = zext i32 %24 to i64
    Value *value31 = builder.CreateZExt(value24, builder.getInt64Ty());

    //   %32 = mul nuw nsw i64 %31, 50
    Value *value32 = builder.CreateMul(value31, builder.getInt64(50), "", true, true);

    //   %33 = getelementptr inbounds [2500 x i8], [2500 x i8]* %1, i64 0, i64 %32
    Value *value33 = builder.CreateInBoundsGEP(arrayType, value1, {builder.getInt64(0), value32});

    //   %34 = mul nuw nsw i64 %26, 50
    Value *value34 = builder.CreateMul(value26, builder.getInt64(50), "", true, true);

    //   %35 = getelementptr inbounds [2500 x i8], [2500 x i8]* %1, i64 0, i64 %34
    Value *value35 = builder.CreateInBoundsGEP(arrayType, value1, {builder.getInt64(0), value34});

    //   br label %40
    builder.CreateBr(bBlock40);

    // 36:
    builder.SetInsertPoint(bBlock36);

    //   %37 = icmp eq i64 %26, 50
    Value *value37 = builder.CreateICmpUGT(value26, builder.getInt64(50));

    //   br i1 %37, label %103, label %38
    builder.CreateCondBr(value37, bBlock103, bBlock38);

    // 38:
    builder.SetInsertPoint(bBlock38);

    //   %39 = phi i64 [ %26, %36 ], [ 0, %235 ]
    PHINode *value39 = builder.CreatePHI(builder.getInt64Ty(), 2);
    //   br label %21, !llvm.loop !13

    // 40:
    builder.SetInsertPoint(bBlock40);

    //   %41 = phi i64 [ 0, %21 ], [ %62, %89 ]
    PHINode *value41 = builder.CreatePHI(builder.getInt64Ty(), 2);

    //   %42 = trunc i64 %41 to i32
    Value *value42 = builder.CreateTrunc(value41, builder.getInt32Ty());

    //   %43 = add i32 %42, -1
    Value *value43 = builder.CreateAdd(value42, builder.getInt32(-1));

    //   %44 = icmp ugt i32 %43, 49
    Value *value44 = builder.CreateICmpUGT(value43, builder.getInt32(49));

    //   %45 = or i1 %25, %44
    Value *value45 = builder.CreateOr(value25, value44);

    //   br i1 %45, label %52, label %46
    builder.CreateCondBr(value45, bBlock52, bBlock46);

    // 46:
    builder.SetInsertPoint(bBlock46);

    //   %47 = zext i32 %43 to i64
    Value *value47 = builder.CreateZExt(value43, builder.getInt64Ty());

    //   %48 = getelementptr inbounds i8, i8* %33, i64 %47
    Value *value48 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value33, value47);

    //   %49 = load i8, i8* %48, align 1, !tbaa !7, !range !12
    Value *value49 = builder.CreateAlignedLoad(builder.getInt8Ty(), value48, align1);

    //   %50 = mul nuw nsw i8 %49, 3
    Value *value50 = builder.CreateMul(value49, builder.getInt8(3), "", true, true);

    //   %51 = zext i8 %50 to i32
    Value *value51 = builder.CreateZExt(value50, builder.getInt32Ty());

    //   br label %52
    builder.CreateBr(bBlock52);

    // 52:
    builder.SetInsertPoint(bBlock52);

    //   %53 = phi i32 [ %51, %46 ], [ 0, %40 ]
    PHINode *value53 = builder.CreatePHI(builder.getInt32Ty(), 2);

    //   br i1 %44, label %59, label %54
    builder.CreateCondBr(value44, bBlock59, bBlock54);

    // 54:
    builder.SetInsertPoint(bBlock54);

    //   %55 = zext i32 %43 to i64
    Value *value55 = builder.CreateZExt(value43, builder.getInt64Ty());

    //   %56 = getelementptr inbounds i8, i8* %29, i64 %55
    Value *value56 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value29, value55);

    //   %57 = load i8, i8* %56, align 1, !tbaa !7, !range !12
    Value *value57 = builder.CreateAlignedLoad(builder.getInt8Ty(), value56, align1);

    //   %58 = zext i8 %57 to i32
    Value *value58 = builder.CreateZExt(value57, builder.getInt32Ty());

    //   br label %59
    builder.CreateBr(bBlock59);

    // 59:
    builder.SetInsertPoint(bBlock59);

    //   %60 = phi i32 [ %58, %54 ], [ 0, %52 ]
    PHINode *value60 = builder.CreatePHI(builder.getInt32Ty(), 2);

    //   %61 = add nuw nsw i32 %60, %53
    Value *value61 = builder.CreateAdd(value60, builder.getInt32(53), "", true, true);

    //   %62 = add nuw nsw i64 %41, 1
    Value *value62 = builder.CreateAdd(value41, builder.getInt64(1), "", true, true);

    //   %63 = icmp ugt i64 %41, 48
    Value *value63 = builder.CreateICmpUGT(value41, builder.getInt64(48));

    //   br i1 %63, label %68, label %64
    builder.CreateCondBr(value63, bBlock68, bBlock64);

    // 64:
    builder.SetInsertPoint(bBlock64);

    //   %65 = getelementptr inbounds i8, i8* %29, i64 %62
    Value *value65 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value29, value62);

    //   %66 = load i8, i8* %65, align 1, !tbaa !7, !range !12
    Value *value66 = builder.CreateAlignedLoad(builder.getInt8Ty(), value65, align1);

    //   %67 = zext i8 %66 to i32
    Value *value67 = builder.CreateZExt(value66, builder.getInt32Ty());

    //   br label %68
    builder.CreateBr(bBlock68);

    // 68:
    builder.SetInsertPoint(bBlock68);

    //   %69 = phi i32 [ %67, %64 ], [ 0, %59 ]
    PHINode *value69 = builder.CreatePHI(builder.getInt32Ty(), 2);

    //   %70 = add nuw nsw i32 %61, %69
    Value *value70 = builder.CreateAdd(value61, value69, "", true, true);

    //   %71 = or i1 %27, %44
    Value *value71 = builder.CreateOr(value27, value44);

    //   br i1 %71, label %77, label %72
    builder.CreateCondBr(value71, bBlock77, bBlock72);

    // 72:
    builder.SetInsertPoint(bBlock72);

    //   %73 = zext i32 %43 to i64
    Value *value73 = builder.CreateZExt(value43, builder.getInt64Ty());

    //   %74 = getelementptr inbounds i8, i8* %35, i64 %73
    Value *value74 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value35, value73);

    //   %75 = load i8, i8* %74, align 1, !tbaa !7, !range !12
    Value *value75 = builder.CreateAlignedLoad(builder.getInt8Ty(), value74, align1);

    //   %76 = zext i8 %75 to i32
    Value *value76 = builder.CreateZExt(value75, builder.getInt32Ty());

    //   br label %77
    builder.CreateBr(bBlock77);

    // 77:
    builder.SetInsertPoint(bBlock77);

    //   %78 = phi i32 [ %76, %72 ], [ 0, %68 ]
    PHINode *value78 = builder.CreatePHI(builder.getInt32Ty(), 2);

    //   %79 = add nuw nsw i32 %70, %78
    Value *value79 = builder.CreateAdd(value70, value78, "", true, true);

    //   br i1 %27, label %89, label %80
    builder.CreateCondBr(value27, bBlock89, bBlock80);

    // 80:
    builder.SetInsertPoint(bBlock80);

    //   %81 = getelementptr inbounds i8, i8* %35, i64 %41
    Value *value81 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value35, value41);

    //   %82 = load i8, i8* %81, align 1, !tbaa !7, !range !12
    Value *value82 = builder.CreateAlignedLoad(builder.getInt8Ty(), value81, align1);

    //   %83 = zext i8 %82 to i32
    Value *value83 = builder.CreateZExt(value82, builder.getInt32Ty());

    //   %84 = add nuw nsw i32 %79, %83
    Value *value84 = builder.CreateAdd(value79, value83, "", true, true);

    //   br i1 %63, label %89, label %85
    builder.CreateCondBr(value63, bBlock89, bBlock85);

    // 85:
    builder.SetInsertPoint(bBlock85);

    //   %86 = getelementptr inbounds i8, i8* %35, i64 %62
    Value *value86 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value35, value62);

    //   %87 = load i8, i8* %86, align 1, !tbaa !7, !range !12
    Value *value87 = builder.CreateAlignedLoad(builder.getInt8Ty(), value86, align1);

    //   %88 = zext i8 %87 to i32
    Value *value88 = builder.CreateZExt(value87, builder.getInt32Ty());

    //   br label %89
    builder.CreateBr(bBlock89);

    // 89:
    builder.SetInsertPoint(bBlock89);

    //   %90 = phi i32 [ %84, %85 ], [ %84, %80 ], [ %79, %77 ]
    PHINode *value90 = builder.CreatePHI(builder.getInt32Ty(), 3);

    //   %91 = phi i32 [ %88, %85 ], [ 0, %80 ], [ 0, %77 ]
    PHINode *value91 = builder.CreatePHI(builder.getInt32Ty(), 3);

    //   %92 = add nuw nsw i32 %91, %90
    Value *value92 = builder.CreateAdd(value91, value90, "", true, true);

    //   %93 = getelementptr inbounds i8, i8* %29, i64 %41
    Value *value93 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value29, value41);

    //   %94 = load i8, i8* %93, align 1, !tbaa !7, !range !12
    Value *value94 = builder.CreateAlignedLoad(builder.getInt8Ty(), value93, align1);

    //   %95 = icmp eq i8 %94, 0
    Value *value95 = builder.CreateICmpEQ(value94, builder.getInt8(0));

    //   %96 = getelementptr inbounds i8, i8* %30, i64 %41
    Value *value96 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value30, value41);

    //   %97 = and i32 %92, -2
    Value *value97 = builder.CreateFAdd(value92, builder.getInt32(-2));

    //   %98 = icmp eq i32 %97, 2
    Value *value98 = builder.CreateICmpEQ(value97, builder.getInt32(2));

    //   %99 = icmp ugt i32 %92, 2
    Value *value99 = builder.CreateICmpUGT(value92, builder.getInt32(2));

    //   %100 = select i1 %95, i1 %99, i1 %98
    Value *value100 = builder.CreateSelect(value95, value99, value98);

    //   %101 = zext i1 %100 to i8
    Value *value101 = builder.CreateZExt(value100, builder.getInt8Ty());

    //   store i8 %101, i8* %96, align 1, !tbaa !7
    builder.CreateAlignedStore(value101, value96, align1);

    //   %102 = icmp eq i64 %62, 50
    Value *value102 = builder.CreateICmpEQ(value62, builder.getInt64(50));

    //   br i1 %102, label %36, label %40, !llvm.loop !14
    builder.CreateCondBr(value102, bBlock36, bBlock40);

    // 103:
    builder.SetInsertPoint(bBlock103);

    //   call void @drawWorld(i8* noundef nonnull %3) #6
    CallInst *call2 = builder.CreateCall(drawWorldFunc, {value3});
    call2->setTailCall(true);

    //   br label %104
    builder.CreateBr(bBlock104);

    // 104:
    builder.SetInsertPoint(bBlock104);

    //   %105 = phi i64 [ 0, %103 ], [ %109, %119 ]
    PHINode *value105 = builder.CreatePHI(builder.getInt64Ty(), 2);

    //   %106 = trunc i64 %105 to i32
    Value *value106 = builder.CreateTrunc(value105, builder.getInt32Ty());

    //   %107 = add i32 %106, -1
    Value *value107 = builder.CreateAdd(value106, builder.getInt32(-1));

    //   %108 = icmp ugt i32 %107, 49
    Value *value108 = builder.CreateICmpUGT(value107, builder.getInt32(49));

    //   %109 = add nuw nsw i64 %105, 1
    Value *value109 = builder.CreateAdd(value105, builder.getInt64(1), "", true, true);

    //   %110 = icmp ugt i64 %105, 48
    Value *value110 = builder.CreateICmpUGT(value105, builder.getInt64(48));

    //   %111 = mul nuw nsw i64 %105, 50
    Value *value111 = builder.CreateMul(value105, builder.getInt64(50), "", true, true);

    //   %112 = getelementptr inbounds [2500 x i8], [2500 x i8]* %2, i64 0, i64 %111
    Value *value112 = builder.CreateInBoundsGEP(arrayType, value2, {builder.getInt64(0), value111});

    //   %113 = getelementptr inbounds [2500 x i8], [2500 x i8]* %1, i64 0, i64 %111
    Value *value113 = builder.CreateInBoundsGEP(arrayType, value1, {builder.getInt64(0), value111});

    //   %114 = zext i32 %107 to i64
    Value *value114 = builder.CreateZExt(value107, builder.getInt64Ty());

    //   %115 = mul nuw nsw i64 %114, 50
    Value *value115 = builder.CreateMul(value114, builder.getInt64(50), "", true, true);

    //   %116 = getelementptr inbounds [2500 x i8], [2500 x i8]* %2, i64 0, i64 %115
    Value *value116 = builder.CreateInBoundsGEP(arrayType, value2, {builder.getInt64(0), value115});

    //   %117 = mul nuw nsw i64 %109, 50
    Value *value117 = builder.CreateMul(value109, builder.getInt64(50), "", true, true);

    //   %118 = getelementptr inbounds [2500 x i8], [2500 x i8]* %2, i64 0, i64 %117
    Value *value118 = builder.CreateInBoundsGEP(arrayType, value2, {builder.getInt64(0), value117});

    //   br label %121
    builder.CreateBr(bBlock121);

    // 119:
    builder.SetInsertPoint(bBlock119);

    //   %120 = icmp eq i64 %109, 50
    Value *value120 = builder.CreateICmpEQ(value109, builder.getInt64(50));

    //   br i1 %120, label %184, label %104, !llvm.loop !13
    builder.CreateCondBr(value120, bBlock184, bBlock104);

    // 121:
    builder.SetInsertPoint(bBlock121);

    //   %122 = phi i64 [ 0, %104 ], [ %143, %170 ]
    PHINode *value122 = builder.CreatePHI(builder.getInt64Ty(), 2);

    //   %123 = trunc i64 %122 to i32
    Value *value123 = builder.CreateTrunc(value122, builder.getInt32Ty());

    //   %124 = add i32 %123, -1
    Value *value124 = builder.CreateAdd(value123, builder.getInt32(-1));

    //   %125 = icmp ugt i32 %124, 49
    Value *value125 = builder.CreateICmpUGT(value124, builder.getInt32(49));

    //   %126 = or i1 %108, %125
    Value *value126 = builder.CreateOr(value108, value125);

    //   br i1 %126, label %133, label %127
    builder.CreateCondBr(value126, bBlock133, bBlock127);

    // 127:
    builder.SetInsertPoint(bBlock127);

    //   %128 = zext i32 %124 to i64
    Value *value128 = builder.CreateZExt(value124, builder.getInt64Ty());

    //   %129 = getelementptr inbounds i8, i8* %116, i64 %128
    Value *value129 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value116, value128);

    //   %130 = load i8, i8* %129, align 1, !tbaa !7, !range !12
    Value *value130 = builder.CreateAlignedLoad(builder.getInt8Ty(), value129, align1);

    //   %131 = mul nuw nsw i8 %130, 3
    Value *value131 = builder.CreateMul(value130, builder.getInt8(3), "", true, true);

    //   %132 = zext i8 %131 to i32
    Value *value132 = builder.CreateZExt(value131, builder.getInt32Ty());

    //   br label %133
    builder.CreateBr(bBlock133);

    // 133:
    builder.SetInsertPoint(bBlock133);

    //   %134 = phi i32 [ %132, %127 ], [ 0, %121 ]
    PHINode *value134 = builder.CreatePHI(builder.getInt32Ty(), 2);

    //   br i1 %125, label %140, label %135
    builder.CreateCondBr(value125, bBlock140, bBlock135);

    // 135:
    builder.SetInsertPoint(bBlock135);

    //   %136 = zext i32 %124 to i64
    Value *value136 = builder.CreateZExt(value124, builder.getInt64Ty());

    //   %137 = getelementptr inbounds i8, i8* %112, i64 %136
    Value *value137 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value112, value136);

    //   %138 = load i8, i8* %137, align 1, !tbaa !7, !range !12
    Value *value138 = builder.CreateAlignedLoad(builder.getInt8Ty(), value137, align1);

    //   %139 = zext i8 %138 to i32
    Value *value139 = builder.CreateZExt(value138, builder.getInt32Ty());

    //   br label %140
    builder.CreateBr(bBlock140);

    // 140:
    builder.SetInsertPoint(bBlock140);

    //   %141 = phi i32 [ %139, %135 ], [ 0, %133 ]
    PHINode *value141 = builder.CreatePHI(builder.getInt32Ty(), 2);

    //   %142 = add nuw nsw i32 %141, %134
    Value *value142 = builder.CreateAdd(value141, value134, "", true, true);

    //   %143 = add nuw nsw i64 %122, 1
    Value *value143 = builder.CreateAdd(value122, builder.getInt64(1), "", true, true);

    //   %144 = icmp ugt i64 %122, 48
    Value *value144 = builder.CreateICmpUGT(value122, builder.getInt64(48));

    //   br i1 %144, label %149, label %145
    builder.CreateCondBr(value144, bBlock149, bBlock145);

    // 145:
    builder.SetInsertPoint(bBlock145);

    //   %146 = getelementptr inbounds i8, i8* %112, i64 %143
    Value *value146 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value112, value143);

    //   %147 = load i8, i8* %146, align 1, !tbaa !7, !range !12
    Value *value147 = builder.CreateAlignedLoad(builder.getInt8Ty(), value146, align1);

    //   %148 = zext i8 %147 to i32
    Value *value148 = builder.CreateZExt(value147, builder.getInt32Ty());

    //   br label %149
    builder.CreateBr(bBlock149);

    // 149:
    builder.SetInsertPoint(bBlock149);

    //   %150 = phi i32 [ %148, %145 ], [ 0, %140 ]
    PHINode *value150 = builder.CreatePHI(builder.getInt32Ty(), 2);

    //   %151 = add nuw nsw i32 %142, %150
    Value *value151 = builder.CreateAdd(value142, value150, "", true, true);

    //   %152 = or i1 %110, %125
    Value *value152 = builder.CreateOr(value110, value125);

    //   br i1 %152, label %158, label %153
    builder.CreateCondBr(value152, bBlock158, bBlock153);

    // 153:
    builder.SetInsertPoint(bBlock153);

    //   %154 = zext i32 %124 to i64
    Value *value154 = builder.CreateZExt(value124, builder.getInt64Ty());

    //   %155 = getelementptr inbounds i8, i8* %118, i64 %154
    Value *value155 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value118, value154);

    //   %156 = load i8, i8* %155, align 1, !tbaa !7, !range !12
    Value *value156 = builder.CreateAlignedLoad(builder.getInt8Ty(), value155, align1);

    //   %157 = zext i8 %156 to i32
    Value *value157 = builder.CreateZExt(value156, builder.getInt32Ty());

    //   br label %158
    builder.CreateBr(bBlock158);

    // 158:
    builder.SetInsertPoint(bBlock158);

    //   %159 = phi i32 [ %157, %153 ], [ 0, %149 ]
    PHINode *value159 = builder.CreatePHI(builder.getInt32Ty(), 2);

    //   %160 = add nuw nsw i32 %151, %159
    Value *value160 = builder.CreateAdd(value151, value159, "", true, true);

    //   br i1 %110, label %170, label %161
    builder.CreateCondBr(value110, bBlock170, bBlock161);

    // 161:
    builder.SetInsertPoint(bBlock161);

    //   %162 = getelementptr inbounds i8, i8* %118, i64 %122
    Value *value162 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value118, value122);

    //   %163 = load i8, i8* %162, align 1, !tbaa !7, !range !12
    Value *value163 = builder.CreateAlignedLoad(builder.getInt8Ty(), value162, align1);

    //   %164 = zext i8 %163 to i32
    Value *value164 = builder.CreateZExt(value163, builder.getInt32Ty());

    //   %165 = add nuw nsw i32 %160, %164
    Value *value165 = builder.CreateAdd(value164, value160, "", true, true);

    //   br i1 %144, label %170, label %166
    builder.CreateCondBr(value144, bBlock170, bBlock166);

    // 166:
    builder.SetInsertPoint(bBlock166);

    //   %167 = getelementptr inbounds i8, i8* %118, i64 %143
    Value *value167 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value118, value143);

    //   %168 = load i8, i8* %167, align 1, !tbaa !7, !range !12
    Value *value168 = builder.CreateAlignedLoad(builder.getInt8Ty(), value167, align1);

    //   %169 = zext i8 %168 to i32
    Value *value169 = builder.CreateZExt(value168, builder.getInt32Ty());

    //   br label %170
    builder.CreateBr(bBlock170);

    // 170:
    builder.SetInsertPoint(bBlock170);

    //   %171 = phi i32 [ %165, %166 ], [ %165, %161 ], [ %160, %158 ]
    PHINode *value171 = builder.CreatePHI(builder.getInt32Ty(), 3);

    //   %172 = phi i32 [ %169, %166 ], [ 0, %161 ], [ 0, %158 ]
    PHINode *value172 = builder.CreatePHI(builder.getInt32Ty(), 3);

    //   %173 = add nuw nsw i32 %172, %171
    Value *value173 = builder.CreateAdd(value172, value171, "", true, true);

    //   %174 = getelementptr inbounds i8, i8* %112, i64 %122
    Value *value174 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value112, value122);

    //   %175 = load i8, i8* %174, align 1, !tbaa !7, !range !12
    Value *value175 = builder.CreateAlignedLoad(builder.getInt8Ty(), value174, align1);

    //   %176 = icmp eq i8 %175, 0
    Value *value176 = builder.CreateICmpEQ(value175, builder.getInt8(0));

    //   %177 = getelementptr inbounds i8, i8* %113, i64 %122
    Value *value177 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value113, value122);

    //   %178 = and i32 %173, -2
    Value *value178 = builder.CreateFAdd(value173, builder.getInt32(-2));

    //   %179 = icmp eq i32 %178, 2
    Value *value179 = builder.CreateICmpUGT(value178, builder.getInt32(2));

    //   %180 = icmp ugt i32 %173, 2
    Value *value180 = builder.CreateICmpUGT(value173, builder.getInt32(2));

    //   %181 = select i1 %176, i1 %180, i1 %179
    Value *value181 = builder.CreateSelect(value176, value180, value179);

    //   %182 = zext i1 %181 to i8
    Value *value182 = builder.CreateZExt(value181, builder.getInt8Ty());

    //   store i8 %182, i8* %177, align 1, !tbaa !7
    builder.CreateAlignedStore(value182, value177, align1);

    //   %183 = icmp eq i64 %143, 50
    Value *value183 = builder.CreateICmpEQ(value143, builder.getInt64(50));

    //   br i1 %183, label %119, label %121, !llvm.loop !14
    builder.CreateCondBr(value183, bBlock119, bBlock121);

    // 184:
    builder.SetInsertPoint(bBlock184);

    //   call void @drawWorld(i8* noundef nonnull %20) #6
    CallInst *call3 = builder.CreateCall(drawWorldFunc, {value20});
    call3->setTailCall(true);

    //   br label %185
    builder.CreateBr(bBlock185);

    // 185:
    builder.SetInsertPoint(bBlock185);

    //   %186 = phi i64 [ 0, %184 ], [ %233, %185 ]
    PHINode *value186 = builder.CreatePHI(builder.getInt64Ty(), 2);

    //   %187 = phi i8 [ 1, %184 ], [ %232, %185 ]
    PHINode *value187 = builder.CreatePHI(builder.getInt8Ty(), 2);

    //   %188 = mul nuw nsw i64 %186, 50
    Value *value188 = builder.CreateMul(value186, builder.getInt64(50), "", true, true);

    //   %189 = getelementptr inbounds [2500 x i8], [2500 x i8]* %1, i64 0, i64 %188
    Value *value189 = builder.CreateInBoundsGEP(arrayType, value1, {builder.getInt64(0), value188});

    //   %190 = getelementptr inbounds [2500 x i8], [2500 x i8]* %2, i64 0, i64 %188
    Value *value190 = builder.CreateInBoundsGEP(arrayType, value2, {builder.getInt64(0), value188});

    //   %191 = getelementptr inbounds i8, i8* %189, i64 32
    Value *value191 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value189, value32);

    //   %192 = bitcast i8* %191 to <16 x i8>*
    Value *value192 = builder.CreateBitCast(value191, byteVector);

    //   %193 = load <16 x i8>, <16 x i8>* %192, align 2, !tbaa !7
    Value *value193 = builder.CreateAlignedLoad(builder.getInt8Ty(), value192, align2);

    //   %194 = getelementptr inbounds i8, i8* %190, i64 32
    Value *value194 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value190, value32);

    //   %195 = bitcast i8* %194 to <16 x i8>*
    Value *value195 = builder.CreateBitCast(value194, byteVector);

    //   %196 = load <16 x i8>, <16 x i8>* %195, align 2, !tbaa !7
    Value *value196 = builder.CreateAlignedLoad(builder.getInt8Ty(), value195, align2);

    //   %197 = icmp eq <16 x i8> %193, %196
    Value *value197 = builder.CreateICmpEQ(value193, value196);

    //   %198 = getelementptr inbounds i8, i8* %189, i64 16
    Value *value198 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value189, builder.getInt64(16));

    //   %199 = bitcast i8* %198 to <16 x i8>*
    Value *value199 = builder.CreateBitCast(value198, byteVector);

    //   %200 = load <16 x i8>, <16 x i8>* %199, align 2, !tbaa !7
    Value *value200 = builder.CreateAlignedLoad(builder.getInt8Ty(), value199, align2);

    //   %201 = getelementptr inbounds i8, i8* %190, i64 16
    Value *value201 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value190, builder.getInt64(16));

    //   %202 = bitcast i8* %201 to <16 x i8>*
    Value *value202 = builder.CreateBitCast(value201, byteVector);

    //   %203 = load <16 x i8>, <16 x i8>* %202, align 2, !tbaa !7
    Value *value203 = builder.CreateAlignedLoad(builder.getInt8Ty(), value202, align2);

    //   %204 = icmp eq <16 x i8> %200, %203
    Value *value204 = builder.CreateICmpEQ(value200, value203);

    //   %205 = select <16 x i1> %197, <16 x i1> %204, <16 x i1> zeroinitializer
    Value *value205 = builder.CreateSelect(value197, value204, UndefValue::get(bitVector));

    //   %206 = bitcast i8* %189 to <16 x i8>*
    Value *value206 = builder.CreateBitCast(value189, byteVector);

    //   %207 = load <16 x i8>, <16 x i8>* %206, align 2, !tbaa !7
    Value *value207 = builder.CreateAlignedLoad(builder.getInt8Ty(), value206, align2);

    //   %208 = bitcast i8* %190 to <16 x i8>*
    Value *value208 = builder.CreateBitCast(value190, byteVector);

    //   %209 = load <16 x i8>, <16 x i8>* %208, align 2, !tbaa !7
    Value *value209 = builder.CreateAlignedLoad(builder.getInt8Ty(), value208, align2);

    //   %210 = icmp eq <16 x i8> %207, %209
    Value *value210 = builder.CreateICmpEQ(value207, value209);

    //   %211 = select <16 x i1> %205, <16 x i1> %210, <16 x i1> zeroinitializer
    Value *value211 = builder.CreateSelect(value205, value210, ConstantAggregateZero::get(bitVector));

    //   %212 = insertelement <16 x i8> poison, i8 %187, i64 0
    Value *value212 = builder.CreateInsertElement(PoisonValue::get(byteVector), value187, builder.getInt64(0));

    //   %213 = shufflevector <16 x i8> %212, <16 x i8> poison, <16 x i32> zeroinitializer
    Value *value213 = builder.CreateShuffleVector(value212, PoisonValue::get(byteVector), ConstantAggregateZero::get(intVector));

    //   %214 = select <16 x i1> %211, <16 x i8> %213, <16 x i8> zeroinitializer
    Value *value214 = builder.CreateSelect(value211, value213, ConstantAggregateZero::get(bitVector));

    //   %215 = insertelement <16 x i8> poison, i8 %187, i64 0
    Value *value215 = builder.CreateInsertElement(PoisonValue::get(byteVector), value187, builder.getInt64(0));

    //   %216 = shufflevector <16 x i8> %215, <16 x i8> poison, <16 x i32> zeroinitializer
    Value *value216 = builder.CreateShuffleVector(value215, PoisonValue::get(byteVector), ConstantAggregateZero::get(intVector));

    //   %217 = icmp ne <16 x i8> %214, %216
    Value *value217 = builder.CreateICmpNE(value214, value216);

    //   %218 = bitcast <16 x i1> %217 to i16
    Value *value218 = builder.CreateBitCast(value217, builder.getInt16Ty());

    //   %219 = icmp eq i16 %218, 0
    Value *value219 = builder.CreateICmpEQ(value218, builder.getInt16(0));

    //   %220 = getelementptr inbounds i8, i8* %189, i64 48
    Value *value220 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value189, builder.getInt64(48));

    //   %221 = load i8, i8* %220, align 2, !tbaa !7, !range !12
    Value *value221 = builder.CreateAlignedLoad(builder.getInt8Ty(), value220, align1);

    //   %222 = getelementptr inbounds i8, i8* %190, i64 48
    Value *value222 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value190, builder.getInt64(48));

    //   %223 = load i8, i8* %222, align 2, !tbaa !7, !range !12
    Value *value223 = builder.CreateAlignedLoad(builder.getInt8Ty(), value222, align1);

    //   %224 = icmp eq i8 %221, %223
    Value *value224 = builder.CreateICmpEQ(value221, value223);

    //   %225 = getelementptr inbounds i8, i8* %189, i64 49
    Value *value225 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value189, builder.getInt64(49));

    //   %226 = load i8, i8* %225, align 1, !tbaa !7, !range !12
    Value *value226 = builder.CreateAlignedLoad(builder.getInt8Ty(), value225, align1);

    //   %227 = getelementptr inbounds i8, i8* %190, i64 49
    Value *value227 = builder.CreateInBoundsGEP(builder.getInt8Ty(), value190, builder.getInt64(49));

    //   %228 = load i8, i8* %227, align 1, !tbaa !7, !range !12
    Value *value228 = builder.CreateAlignedLoad(builder.getInt8Ty(), value227, align1);

    //   %229 = icmp eq i8 %226, %228
    Value *value229 = builder.CreateICmpEQ(value226, value228);

    //   %230 = select i1 %229, i1 %224, i1 false
    Value *value230 = builder.CreateSelect(value229, value224, builder.getInt1(false));

    //   %231 = select i1 %230, i1 %219, i1 false
    Value *value231 = builder.CreateSelect(value230, value219, builder.getInt1(false));

    //   %232 = select i1 %231, i8 %187, i8 0
    Value *value232 = builder.CreateSelect(value231, value187, builder.getInt8(0));

    //   %233 = add nuw nsw i64 %186, 1
    Value *value233 = builder.CreateAdd(value186, builder.getInt64(1), "", true, true);

    //   %234 = icmp eq i64 %233, 50
    Value *value234 = builder.CreateICmpEQ(value233, builder.getInt64(50));

    //   br i1 %234, label %235, label %185, !llvm.loop !15
    builder.CreateCondBr(value234, bBlock235, bBlock185);

    // 235:
    builder.SetInsertPoint(bBlock235);

    //   %236 = and i8 %232, 1
    Value *value236 = builder.CreateFAdd(value232, builder.getInt8(1));

    //   %237 = icmp eq i8 %236, 0
    Value *value237 = builder.CreateICmpEQ(value236, builder.getInt8(0));

    //   br i1 %237, label %38, label %238
    builder.CreateCondBr(value237, bBlock38, bBlock238);

    // 238:
    builder.SetInsertPoint(bBlock238);

    //   ret void
    builder.CreateRetVoid();

    /*
      Now resolve all PHI nodes
    */

    value5->addIncoming(builder.getInt64(0), bBlock0);
    value5->addIncoming(value9, bBlock8);

    value12->addIncoming(builder.getInt64(0), bBlock4);
    value12->addIncoming(value17, bBlock11);

    value22->addIncoming(builder.getInt64(0), bBlock19);
    value22->addIncoming(value39, bBlock38);

    value39->addIncoming(value26, bBlock36);
    value39->addIncoming(builder.getInt64(0), bBlock235);

    value41->addIncoming(builder.getInt64(0), bBlock21);
    value41->addIncoming(value62, bBlock89);

    value53->addIncoming(value51, bBlock46);
    value53->addIncoming(builder.getInt32(0), bBlock40);

    value60->addIncoming(value58, bBlock54);
    value60->addIncoming(builder.getInt32(0), bBlock52);

    value69->addIncoming(value67, bBlock64);
    value69->addIncoming(builder.getInt32(0), bBlock59);

    value78->addIncoming(value76, bBlock72);
    value78->addIncoming(builder.getInt32(0), bBlock68);

    value90->addIncoming(value84, bBlock85);
    value90->addIncoming(value84, bBlock80);
    value90->addIncoming(value79, bBlock77);

    value91->addIncoming(value88, bBlock85);
    value91->addIncoming(builder.getInt32(0), bBlock80);
    value91->addIncoming(builder.getInt32(0), bBlock77);

    value105->addIncoming(builder.getInt64(0), bBlock103);
    value105->addIncoming(value109, bBlock119);

    value122->addIncoming(builder.getInt64(0), bBlock104);
    value122->addIncoming(value143, bBlock170);

    value134->addIncoming(value132, bBlock127);
    value134->addIncoming(builder.getInt32(0), bBlock121);

    value141->addIncoming(value139, bBlock135);
    value141->addIncoming(builder.getInt32(0), bBlock133);

    value150->addIncoming(value148, bBlock145);
    value150->addIncoming(builder.getInt32(0), bBlock140);

    value159->addIncoming(value157, bBlock153);
    value159->addIncoming(builder.getInt32(0), bBlock149);

    value171->addIncoming(value165, bBlock166);
    value171->addIncoming(value165, bBlock161);
    value171->addIncoming(value160, bBlock158);

    value172->addIncoming(value169, bBlock166);
    value172->addIncoming(builder.getInt32(0), bBlock161);
    value172->addIncoming(builder.getInt32(0), bBlock158);

    value186->addIncoming(builder.getInt64(0), bBlock184);
    value186->addIncoming(value233, bBlock185);

    value187->addIncoming(builder.getInt8(1), bBlock184);
    value187->addIncoming(value232, bBlock185);
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
      if (fnName == "rand") {
        return reinterpret_cast<void *>(rand);
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
