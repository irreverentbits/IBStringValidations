// Copyright (c) 2013-2017 Irreverent Bits
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#import "IBStringValidator.h"


typedef enum
{
    VALID = 0x00,
	LENGTH_SHORT = 0x01,
	LENGTH_LONG = 0x02,
    REGEX_INVALID = 0x04
} IBStringValidatorFlags;


@interface IBStringValidator ()

@property (nonatomic, strong) NSRegularExpression *regex;

@property (nonatomic, readwrite, assign) NSUInteger validityFlags;
@property (nonatomic, readwrite, assign) BOOL isValid;
@property (nonatomic, readwrite, assign) BOOL isLengthValid;
@property (nonatomic, readwrite, assign) BOOL isRegexValid;

@property (nonatomic, strong) NSNumber* previousValidity;

@end


@implementation IBStringValidator

#pragma mark - Validity methods

- (id)initWithValidationMinLength:(NSNumber*)minLength maxLength:(NSNumber*)maxLength regexPattern:(NSString*)regexPattern;
{
	self = [super init];
	
	if (self)
	{
		[self setValidationMinLength:minLength maxLength:maxLength regexPattern:regexPattern];
	}
	
	return self;
}

- (void)setValidationMinLength:(NSNumber*)minLength maxLength:(NSNumber*)maxLength regexPattern:(NSString*)regexPattern;
{
    self.minLength = minLength;
    self.maxLength = maxLength;
	self.regexPattern = regexPattern;
	
	if (self.regexPattern)
	{
		NSError * __autoreleasing error;
		self.regex = [NSRegularExpression regularExpressionWithPattern:self.regexPattern options:0 error:&error];
		
		if (error)
		{
			NSLog(@"ERROR: Regex could not be generated from regex pattern '%@' with error: %@", self.regexPattern, [error localizedDescription]);
		}
	}
}

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context
{
	if ([keyPath isEqualToString:@"text"])
	{
		NSString *text = [object valueForKeyPath:keyPath];
		
		[self updateValidityForString:text];
	}
}

- (void)updateValidityForString:(NSString*)testString;
{
	_validityFlags = VALID;
	
    if ([self isLengthShortForString:testString])
    {
        _validityFlags |= LENGTH_SHORT;
    }
    else
    {
        _validityFlags &= ~LENGTH_SHORT;
    }
	
	if ([self isLengthLongForString:testString])
	{
		_validityFlags |= LENGTH_LONG;
	}
	else
	{
		_validityFlags &= ~LENGTH_LONG;
	}
    
    if ([self isRegexValidForString:testString])
    {
        _validityFlags &= ~REGEX_INVALID;
    }
    else
    {
        _validityFlags |= REGEX_INVALID;
    }
    
    self.isValid = (_validityFlags == VALID);
    self.isLengthValid = (((_validityFlags & LENGTH_SHORT) != LENGTH_SHORT) && ((_validityFlags & LENGTH_LONG) != LENGTH_LONG));
    self.isRegexValid = ((_validityFlags & REGEX_INVALID) != REGEX_INVALID);
	
	if (self.previousValidity && ([self.previousValidity boolValue] != self.isValid))
	{
		// Validity changed, call one of the callback blocks
		if (self.isValid)
		{
			if (self.validBlock)
			{
				self.validBlock(self);
			}
		}
		else
		{
			if (self.invalidBlock)
			{
				self.invalidBlock(self);
			}
		}
	}
	
	self.previousValidity = [NSNumber numberWithBool:self.isValid];
}

- (void)setValidBlock:(IBStringValidatorBlock)validBlock;
{
	_validBlock = validBlock;
	
	if (self.isValid)
	{
		_validBlock(self);
	}
}

- (void)setInvalidBlock:(IBStringValidatorBlock)invalidBlock
{
	_invalidBlock = invalidBlock;
	
	if (!self.isValid)
	{
		_invalidBlock(self);
	}
}

- (BOOL)isValidForString:(NSString*)testString;
{
    return ([self isLengthValidForString:testString] && [self isRegexValidForString:testString]);
}

- (BOOL)isLengthShortForString:(NSString*)testString;
{
	// Note: If minLength is not set, then any length is valid
	return (self.minLength && ([testString length] < [self.minLength unsignedIntegerValue]));
}

- (BOOL)isLengthLongForString:(NSString*)testString;
{
	// Note: If maxLength is not set, then any length is valid
	return (self.maxLength && ([testString length] > [self.maxLength unsignedIntegerValue]));
}

- (BOOL)isLengthValidForString:(NSString*)testString;
{
	return (![self isLengthShortForString:testString] && ![self isLengthLongForString:testString]);
}

- (BOOL)isRegexValidForString:(NSString*)testString;
{
    if (self.regex)
    {
        NSUInteger numMatches = [self.regex numberOfMatchesInString:testString options:0 range:NSMakeRange(0, [testString length])];
        
		return (numMatches > 0);
    }
    
    // If regex is not set, then any string is valid
    return YES;
}

@end
