from pymongo import MongoClient
from bson.objectid import Objectid
from pymongo import cursor
from bson.json_util import dumps

class AnimalShelter(object):
    """ CRUD operations for Animal collection in MongoDB """
    
    def __init__(self):
        # Initializing the MongoClient. This helps to access the MongoDB
        # databases and collections. This is hard-wired to use the aac
        # database, the animal collection, and the aac user. Definitions of the
        # connection string variables are unique to the inividual Apporto
        # environment.
        
        # You must edit connection variables below to reflect you own instance
        # of MongoDB
        
        # Connection Variables
        """ It should be understood, that as my CS340 course is finished, I
            no longer have access to MongoDB. This is specifically just the
            code that I used, and updated to reflect the changes that I have
            made within it."""
            
        USER = 'aacuser'
        PASS = 'abc123'
        HOST = 'nv-desktop-services.apporto.com'
        PORT = 33553
        DB = 'AAC'
        COL = 'animals'
        
        # Intialize Connection
        self.client = MongoClient('mongodb://%s:%s@%s:%d' % (USER,PASS,HOST,PORT))
        self.database = self.client['%s' % (DB)]
        self.collection = self.database['%s' % (COL)]
        
    # The next function is a part of the CRUD method, or more specifically the
    # C, which stands for Create. I will be adding another function here that
    # was not in the code before moving on to the next step of the method.
    def create(self, data: dict) -> bool:
        """ This function creates a document into the database """
        if data is not None and type(data) is dict:
            try:
                self.database.animals.insert_one(data)
                return True
            except Exception as e:
                print("Exception: ", e)
                return False
        else:
            raise Exception("The data parameter is non-existent, there is "
                            "nothing to save")
            
    # The next function was not part of the initial assignment as it was not
    # required. But, I have decided to add an insert many function which allows
    # the program to create more than one document at a time.
    def createMany(self, data:dict) -> bool:
        """ This function creates multiple documents into the database """
        if data is not None and type(data) is dict:
            try:
                self.database.animals.insert_many(data);
                return True
            except Exception as e:
                print("Exception: ", e)
                return False
        else:
            raise Exception("The data parameter is non-existent, there is "
                            "nothing to save")
                
    # The next function is a part of the CRUD method, or more specifically the
    # R, which stands for Read.
    def read(self, query:dict) -> cursor.Cursor:
        """ This function queries the result of a search from the database """
        if query is not None and type(query) is dict:
            return self.database.animals.find(query, {"_id":False})
        else:
            raise Exception("There is nothing that matches your query in the "
                            "database")
    
    # The next function is a part of the CRUD method, or more specifically the
    # U, which stands for Update. I will be adding another function here that
    # was not in the code before moving on to the next step of the method.
    def updateOne(self, query: dict, changes: dict) -> str:
        """ This function updates a document in the database """
        if (query is not None and type(query) is dict) and (changes is not None and type(changes) is dict):
            updated = self.database.animals.update_one(query, changes)
            return dumps(updated.raw_results)
        else:
            raise Exception("There is nothing to update in the database")
            
    # The next function was not part of the initial assignment as it was not
    # required. But, I have decided to add an update many function which allows
    # the program to update more than one document at a time.
    def updateMany(self, query: dict, changes: dict) -> str:
        """ This function updates multiple documents in the database """
        if (query is not None and type(query) is dict) and (changes is not None and type(changes) is dict):
            updated = self.database.animals.update_many(query, changes)
            return dumps(updated.raw_results)
        else:
            raise Exception("There is nothing to update in the database")
            
    # The next function is the final part of the CRUD method, or more
    # specifically the D, which stands for Delete. I will be adding another
    # function here that was not in the code before moving on to some other
    # additions that I have decided to make.
    def deleteOne(self, remove: dict) -> str:
        """ This function deletes a single document from the database """
        if remove is not None and type(remove) is dict:
            deleted = self.database.animals.delete_one(remove)
            return dumps(deleted.raw_results)
        else:
            raise Exception("There is nothing to delete in the database")
            
    # The next function was not part of the initial assignment as it was not
    # required. But, I have decided to add a delete function which allows the
    # program to delete more than one document as a time.
    def deleteMany(self, remove: dict) -> str:
        """ This function deletes multiple documents from the database """
        if remove is not None and type(remove) is dict:
            deleted = self.database.animals.delete_many(remove)
            return dumps(deleted.raw_result)
        else:
            raise Exception("There is nothing to delete in the database")
            
    # The next two functions are not a part of the original CRUD method, but
    # I thought that they would be a nice addition, to show my competance.
    
    # The first function replaces a single document.
    def replaceOne(self, query: dict, changes: dict) -> str:
        """ This function replaces a single document from the database """
        if (query is not None and type(query) is dict) and (changes is not None and type(changes) is dict):
            replaced = self.database.animals.replace_one(query, changes)
            return dumps(replaced.raw_results)
        else:
            raise Exception("There is nothing to replace in the database")
            
    # The next function will replace multiple documents
    def replaceMany(self, query: dict, changes: dict) -> str:
        """ This function replaces multiple documents from the database """
        if (query is not None and type(query) is dict) and (changes is not None and type(changes) is dict):
            replaced = self.database.animals.replace_many(query, changes)
            return dumps(replaced.raw_results)
        else:
            raise Exception("There is nothing to replace in the database")