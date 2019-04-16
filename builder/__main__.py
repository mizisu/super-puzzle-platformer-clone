import builder.simplebuilder as simplebuilder
import asyncio


async def main():
    await simplebuilder.build('.')
    pass

if __name__ == "__main__":
    asyncio.run(main())
    # simplebuilder.build('.')
    
