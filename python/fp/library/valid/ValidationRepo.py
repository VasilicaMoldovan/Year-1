from entities.Entities import Book, Client, Rental

class ValidError(Exception):
    pass

class RepoError(Exception):
    pass

class RepoValidator():
    def __init__(self, __bookRepo, __clientRepo):
        self.__bookRepo = __bookRepo
        self.__clientRepo = __clientRepo
        
    def validRepo(self, element):
        errors = ""
        book = element.get_book_id()
        client = element.get_client_id()
        search = self.__bookRepo.searchElement1(Book(book))
        if search == -1:
            errors += "this book doesn't exist\n"
        search = self.__clientRepo.searchElement1(Client(client))
        if search == -1:
            errors += "this client doesn't exist\n"
        if len(errors) > 0:
            raise RepoError(errors)
        
    def validRent(self, params):
        errors = ""
        from datetime import date
        words = params.split(".")
        try:
            words[0] = int(words[0])
        except:
            errors += "invalid date\n"
        try:
            words[1] = int(words[1])
        except:
            errors += "invalid date\n"
        try:
            words[2] = int(words[2])
        except:
            errors += "invalid date\n"
        if len(errors) > 0:
            raise RepoError("invalid date")
        date = date(words[2], words[1], words[0])
        
    def validRent1(self, rent):
        from datetime import date
        date0 = rent.get_rented_date().split(".")
        date0[0] = int(date0[0])
        date0[1] = int(date0[1])
        date0[2] = int(date0[2])
        date1 = date(date0[2], date0[1], date0[0])
        date0 = rent.get_due_date().split(".")
        date0[0] = int(date0[0])
        date0[1] = int(date0[1])
        date0[2] = int(date0[2])
        date2 = date(date0[2], date0[1], date0[0])
        delta = date2 - date1
        if delta.days < 0:
            raise RepoError("invalid rent dates")
    
    def validNewRent(self, new_rent, old_rent):
        errors = ""
        from datetime import date
        date0 = new_rent.get_rented_date().split(".")
        date0[0] = int(date0[0])
        date0[1] = int(date0[1])
        date0[2] = int(date0[2])
        date1 = date(date0[2], date0[1], date0[0])
        if old_rent.get_returned_date() == 0:
            errors += "the book wasn't returned\n"
        else:
            date0 = old_rent.get_returned_date().split(".")
            date0[0] = int(date0[0])
            date0[1] = int(date0[1])
            date0[2] = int(date0[2])
            date2 = date(date0[2], date0[1], date0[0])
            if date1 < date2:
                errors += "this book is currently rented"
        if len(errors) > 0:
            raise RepoError(errors)    

