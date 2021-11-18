class NativeFunctions:
    @staticmethod
    def system_print(args):
        print(args[0], end=' ')

    @staticmethod
    def system_println(args):
        print(args[0])